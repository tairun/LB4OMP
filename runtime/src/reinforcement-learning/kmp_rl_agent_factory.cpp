#include <string>
#include <iostream>

#include "kmp_rl_agent_factory.h"
#include "agents/kmp_q_learner_old.h"
#include "agents/kmp_sarsa_learner_old.h"
#include "agents/kmp_q_learner.h"
#include "agents/kmp_sarsa_learner.h"
#include "agents/kmp_doubleq_learner.h"
#include "agents/kmp_qv_learner.h"
#include "agents/kmp_r_learner.h"
#include "agents/kmp_deepq_learner.h"


// public
int RLAgentFactory::rlAgentSearch(const std::string& loop_id, int agent_type, LoopData* stats, int portfolio_size)
{
    if (!RLAgentFactory::GetTimesteps().count(loop_id)) {
        RLAgentFactory::GetTimesteps().insert(std::make_pair(loop_id, 1));
        std::cout << "[Reinforcement Learning] Creating agent for loop: " << loop_id << std::endl;
        auto* agent = create_agent(agent_type, portfolio_size, portfolio_size, 6);
        RLAgentFactory::GetAgents().insert(std::make_pair(loop_id, agent));
        std::cout << "[Reinforcement Learning] Agent created" << std::endl;
        return 0; // Selects first DLS method for exploration
    } else {
        auto* agent = RLAgentFactory::GetAgents().find(loop_id)->second;
        int new_method = agent->step(RLAgentFactory::GetTimesteps().at(loop_id), stats);
        std::cout << "[Reinforcement Learning] Timestep " << RLAgentFactory::GetTimesteps().at(loop_id) << " completed. New method is " << new_method << std::endl;
        RLAgentFactory::GetTimesteps().at(loop_id)++;
        return new_method;
    }
}

RLAgent* RLAgentFactory::create_agent(int agent_type, int states, int actions, int offset = 0)
{
    RLAgent* agent = nullptr;
    int new_type = agent_type - offset;

    switch (new_type) {
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
            agent = new SARSALearner(states, actions);
            break;
        case (4):
            agent = new DoubleQLearner(states, actions);
            break;
        case (5):
            agent = new QVLearner(states, actions);
            break;
        case (6):
            agent = new RLearner(states, actions);
            break;
        case (7):
            agent = new DeepQLearner(states, actions);
            break;
        case (8):
            agent = new ChunkLearner(states, actions);
            break;
        default:
            std::cout << "[Reinforcement Learning] Unknown agent type specified: " << agent_type << std::endl;
    }

    return agent;
}

// private
std::unordered_map<std::string, int>& RLAgentFactory::GetTimesteps()
{
    static auto* timesteps = new std::unordered_map<std::string, int>();
    return *timesteps;
}

std::unordered_map<std::string, RLAgent*>& RLAgentFactory::GetAgents()
{
    static auto* agents = new std::unordered_map<std::string, RLAgent*>();
    return *agents;
}