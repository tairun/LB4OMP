#include <string>
#include <iostream>
#include "kmp_rl_agent_factory.h"
#include "agents/kmp_q_learner_old.h"
#include "agents/kmp_sarsa_learner_old.h"
#include "agents/kmp_r_learner.h"

int RLAgentFactory::rlAgentSearch(const std::string& loop_id, int agent_type, LoopData* stats, int portfolio_size)
{
    //TODO: Make print statement here (with thread ID)
    if (!RLAgentFactory::GetTimesteps().count(loop_id)) {
        RLAgentFactory::GetTimesteps().insert(std::make_pair(loop_id, 1));
        auto* agent = create_agent(agent_type, portfolio_size, portfolio_size, 6);
        RLAgentFactory::GetAgents().insert(std::make_pair(loop_id, agent));
        std::cout << "[Reinforcement Learning] Agent created" << std::endl;
        return 0; // Selects first DLS method for exploration
    } else {
        auto* agent = RLAgentFactory::GetAgents().find(loop_id)->second;
        int new_method = agent->doLearning(RLAgentFactory::GetTimesteps().at(loop_id), stats);
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
        case (0): // Q-Learner Old
            agent = new QLearnerOld(states, actions);
            break;
        case (1): // SARSA-Learner Old
            agent = new SARSALearnerOld(states, actions);
            break;
        case (2): // R-Learner (New)
            agent = new RLearner(states, actions);
            break;
        default:
            std::cout << "[Reinforcement Learning] Unknown agent type specified: " << agent_type << std::endl;
    }

    return agent;
}

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