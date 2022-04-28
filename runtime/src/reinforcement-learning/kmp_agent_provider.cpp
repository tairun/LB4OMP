// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <string>
#include <iostream>
#include <iomanip>

#include "utils/utils.h"
#include "kmp_agent_provider.h"

#include "initializers/kmp_init_type.h"
#include "initializers/kmp_zero_init.h"
#include "initializers/kmp_random_init.h"
#include "initializers/kmp_optimistic_init.h"

#include "policies/kmp_policy_type.h"
#include "policies/kmp_explore_first_policy.h"
#include "policies/kmp_epsilon_greedy_policy.h"
#include "policies/kmp_softmax_policy.h"

#include "agents/kmp_agent.h"
#include "agents/kmp_q_learner_old.h"
#include "agents/kmp_sarsa_learner_old.h"
#include "agents/kmp_q_learner.h"
#include "agents/kmp_sarsa_learner.h"
#include "agents/kmp_expected_sarsa_learner.h"
#include "agents/kmp_doubleq_learner.h"
#include "agents/kmp_qv_learner.h"
#include "agents/kmp_r_learner.h"
#include "agents/kmp_deepq_learner.h"


int* AgentProvider::chunk_sizes;  // Stores the values of the chunk-sizes for the agent to try

AgentProvider& AgentProvider::Get() {
    static AgentProvider instance;
    return instance;
}

AgentProvider::AgentProvider()
{
    std::string fileData = read_env_string("KMP_RL_AGENT_STATS");
    ofs.open(fileData, std::ofstream::out | std::ofstream::app);
    ofs << "loop_id,timestep,alpha,epsilon,reward,low,high" << std::endl;
}

AgentProvider::~AgentProvider()
{
    ofs.close();
}

// public
int AgentProvider::search(const std::string& loop_id, int agent_type, LoopData* stats, int dimension)
{
    std::cout << "[AgentProvider::search] Loop: " << loop_id << std::endl;
    if (!AgentProvider::get_timesteps().count(loop_id))
    {
        if(agent_type == 15)
        // Change some stuff only for the ChunkLearner!
        // Init the data structure and calculate the chunk-sizes to try
        {
            std::cout << "[AgentProvider::search] Creating ChunkLearner for loop: " << loop_id << std::endl;
            chunk_sizes = new int[dimension];
            calculate_chunks(chunk_sizes, dimension, stats->n, stats->p);
            agent_type = read_env_int("KMP_RL_CHUNK_TYPE"); // Overwrites the agent type from 'ChunkLearner' to the new subtype to be used.
        }

        std::cout << "[AgentProvider::search] Creating agent for loop: " << loop_id << std::endl;
        AgentProvider::get_timesteps().insert(std::make_pair(loop_id, 1));
        auto* agent = create_agent(agent_type, stats, dimension, dimension, 6); // The offset denotes the auto-methods already present in LB4OMP, so we can start our switch statement at 0
        AgentProvider::get_agents().insert(std::make_pair(loop_id, agent));
        std::cout << "[AgentProvider::search] Agent created." << std::endl;
        print_agent_params(loop_id, agent);
        print_agent_stats(loop_id, 0, agent);

        return 0; // Selects first DLS method for exploration
    }
    else
    {
        //std::cout << "[AgentProvider::search] Grabbing agent ..." << std::endl;
        auto* agent = AgentProvider::get_agents().find(loop_id)->second;
        //std::cout << "[AgentProvider::search] Grabbing timestep info ..." << std::endl;
        int new_method = agent->step(0, AgentProvider::get_timesteps().at(loop_id), stats);
        int timestep = AgentProvider::get_timesteps().at(loop_id);
        std::cout << "[AgentProvider::search] Timestep " << timestep << " completed. New method is " << new_method << std::endl;
        AgentProvider::get_timesteps().at(loop_id)++;
        print_agent_stats(loop_id, timestep, agent);

        if(agent_type == 15)
            // Change some stuff only for the ChunkLearner!
            // Translate the action index to the actual chunk-size and return that instead
        {
            std::cout << "[AgentProvider::search] Translating action index to chunk size" << std::endl;
            new_method = chunk_sizes[new_method];
        }

        return new_method;
    }
}

Agent* AgentProvider::create_agent(int agent_type, LoopData* stats, int states, int actions, int offset = 0)
{
    Agent* agent = nullptr;
    int new_type = agent_type - offset;

    std::cout << "[AgentProvider::create_agent] New agent option: " << agent_type << " (offset: " << new_type << ")" << std::endl;

    switch (new_type)
    {
        case (0):
            agent = new QLearnerOld(states, actions);
            break;
        case (1):
            agent = new SARSALearnerOld(states, actions);
            break;
        case (2):
            agent = new QLearner(states, actions);
            break;
        case (3):
            agent = new DoubleQLearner(states, actions);
            break;
        case (4):
            agent = new SARSALearner(states, actions);
            break;
        case (5):
            agent = new ExpectedSARSALearner(states, actions);
            break;
        case (6):
            agent = new QVLearner(states, actions);
            break;
        case (7):
            agent = new RLearner(states, actions);
            break;
        case (8):
            agent = new DeepQLearner(states, actions);
            break;
        default:
            std::cout << "[AgentProvider::create_agent] Unknown agent type specified: " << agent_type << " . Using default (Q-Learner)." << std::endl;
            agent = new QLearner(states, actions);
            break;
    }

    if (new_type == 0 || new_type == 1)
    // Only set initializer and policy when we have a new agent
    {
        std::cout << "[AgentProvider::create_agent] Skipping initializer and policy creation for old agents." << std::endl;
    }
    else
    {
        BaseInit* init = create_initializer(agent);
        std::cout << "[AgentProvider::create_agent] Created initializer successfully." << std::endl;
        agent->set_initializer(init);
        std::cout << "[AgentProvider::create_agent] Set initializer successfully." << std::endl;

        BasePolicy* pol = create_policy(agent);
        std::cout << "[AgentProvider::create_agent] Created policy successfully." << std::endl;
        agent->set_policy(pol);
        std::cout << "[AgentProvider::create_agent] Set policy successfully." << std::endl;
    }

    return agent;
}

std::unordered_map<std::string, int>& AgentProvider::get_timesteps()
{
        return Get().timesteps;
}

std::unordered_map<std::string, Agent*>& AgentProvider::get_agents()
{
    return Get().agents;
}

std::fstream& AgentProvider::get_filestream()
{
    return Get().ofs;
}

BaseInit* AgentProvider::create_initializer(Agent* agent)
{
    BaseInit* init;

    switch (agent->get_init_input()) {
        case InitType::ZERO:
            init = new ZeroInit();
            break;
        case InitType::RANDOM:
            init = new RandomInit();
            break;
        case InitType::OPTIMISTIC:
            init = new OptimisticInit();
            break;
        default:
            init = new ZeroInit();
            break;
    }

 return init;

}

BasePolicy* AgentProvider::create_policy(Agent* agent)
{
    BasePolicy* pol;

    switch (agent->get_policy_input()) {
        case PolicyType::EXPLORE_FIRST:
            pol = new ExploreFirstPolicy();
            break;
        case PolicyType::EPSILON_GREEDY:
            pol = new EpsilonGreedyPolicy();
            break;
        case PolicyType::SOFTMAX:
            pol = new SoftmaxPolicy();
            break;
        default:
            pol = new ExploreFirstPolicy();
            break;
    }

    return pol;
}

int AgentProvider::calculate_chunks(int *array, int size, int n, int p)
{
    for (int i = 1; i <= size; i++)
    {
        array[i-1] = n/(2^i * p);
    }
}

void AgentProvider::print_agent_params(const std::string& loop_id, Agent* agent)
{
    std::fstream ofs;
    std::string fileData = read_env_string("KMP_RL_AGENT_STATS");
    ofs.open(fileData + ".ini", std::fstream::in | std::fstream::out | std::fstream::app);
    ofs << std::fixed << std::setprecision(2);
    ofs << "[PARAMS-"<< loop_id << "]" << std::endl;
    ofs << "Name = "            << agent->get_name() << std::endl;
    ofs << "RewardType = "      << RewardLookup.at(agent->get_reward_type()) << std::endl;
    ofs << "InitType = "        << InitLookup.at(agent->get_init_type()) << std::endl;
    ofs << "PolicyType = "      << PolicyLookup.at(agent->get_policy_type()) << std::endl;
    ofs << "Alpha = "           << agent->get_alpha_init() << std::endl;
    ofs << "AlphaMin = "        << agent->get_alpha_min() << std::endl;
    ofs << "AlphaFactor = "     << agent->get_alpha_decay() << std::endl;
    ofs << "Gamma = "           << agent->get_gamma() << std::endl;
    ofs << "Epsilon = "         << agent->get_epsilon_init() << std::endl;
    ofs << "EpsilonMin = "      << agent->get_epsilon_min() << std::endl;
    ofs << "EpsilonFactor = "   << agent->get_epsilon_decay() << std::endl;
    ofs << std::endl;

    ofs.close();
}

void AgentProvider::print_agent_stats(const std::string& loop_id, int timestep, Agent* agent) {
    AgentProvider::get_filestream() << loop_id << "," << timestep << "," << agent->get_alpha() << "," << agent->get_epsilon() << "," << agent->get_current_reward() << "," << agent->get_low() << "," << agent->get_high() << std::endl;
}
