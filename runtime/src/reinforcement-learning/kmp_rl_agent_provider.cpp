// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <string>
#include <iostream>

#include "kmp_rl_agent_provider.h"
#include "agents/kmp_rl_agent.h"
#include "agents/kmp_q_learner_old.h"
#include "agents/kmp_sarsa_learner_old.h"
#include "agents/kmp_q_learner.h"
#include "agents/kmp_sarsa_learner.h"
#include "agents/kmp_expected_sarsa_learner.h"
#include "agents/kmp_doubleq_learner.h"
#include "agents/kmp_qv_learner.h"
#include "agents/kmp_r_learner.h"
#include "agents/kmp_deepq_learner.h"
#include "agents/kmp_chunk_learner.h"

RLAgentProvider& RLAgentProvider::Get() {
    static RLAgentProvider instance;
    return instance;
}

// public
int RLAgentProvider::rlAgentSearch(const std::string& loop_id, int agent_type, LoopData* stats, int portfolio_size)
{
    if (!RLAgentProvider::get_timesteps().count(loop_id))
    {
        std::cout << "[Reinforcement Learning] Creating agent for loop: " << loop_id << std::endl;
        RLAgentProvider::get_timesteps().insert(std::make_pair(loop_id, 1));
        auto* agent = create_agent(agent_type, stats,portfolio_size, portfolio_size, 6);
        RLAgentProvider::get_agents().insert(std::make_pair(loop_id, agent));
        std::cout << "[Reinforcement Learning] Agent created" << std::endl;
        return 0; // Selects first DLS method for exploration
    }
    else
    {
        std::cout << "[Reinforcement Learning] Grabbing agent ..." << std::endl;
        auto* agent = RLAgentProvider::get_agents().find(loop_id)->second;
        std::cout << "[Reinforcement Learning] Grabbing timestep info ..." << std::endl;
        int new_method = agent->step(0, RLAgentProvider::get_timesteps().at(loop_id), stats);
        std::cout << "[Reinforcement Learning] Timestep " << RLAgentProvider::get_timesteps().at(loop_id) << " completed. New method is " << new_method << std::endl;
        RLAgentProvider::get_timesteps().at(loop_id)++;
        return new_method;
    }
}

RLAgent* RLAgentProvider::create_agent(int agent_type, LoopData* stats, int states, int actions, int offset = 0)
{
    RLAgent* agent = nullptr;
    int new_type = agent_type - offset;

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
        case (9):
            agent = new ChunkLearner(states, actions, stats);
            break;
        default:
            std::cout << "[Reinforcement Learning] Unknown agent type specified: " << agent_type << std::endl;
    }

    return agent;
}

std::unordered_map<std::string, int>& RLAgentProvider::get_timesteps()
{
        return Get().timesteps;
}

std::unordered_map<std::string, RLAgent*>& RLAgentProvider::get_agents()
{
    return Get().agents;
}

void RLAgentProvider::add_csv_data()
{

}

void RLAgentProvider::write_csv_data()
{

}
