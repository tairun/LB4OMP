#include <string>
#include <iostream>

#include "kmp_rl_agent_factory.h"
#include "agents/kmp_q_learner_old.h"
//#include "agents/kmp_sarsa_learner_old.h"

int RLAgentFactory::rlAgentSearch(const std::string& loop_id, int agent_type, double reward_signal, int portfolio_size) {
    //TODO: Make print statement here (with thread ID)
    std::cout << "We got here with " << loop_id << std::endl;
    if (!RLAgentFactory::GetTimesteps().count(loop_id)) {
        RLAgentFactory::GetTimesteps().insert(std::make_pair(loop_id, 0));
        auto* agent = create_agent(loop_id, agent_type, portfolio_size, portfolio_size, 6);
        std::cout << "We got here again" << std::endl;
        RLAgentFactory::GetAgents().insert(std::make_pair(loop_id, agent));
        std::cout << "Agent created" << std::endl;
        return 0;
    } else {
        auto agent = RLAgentFactory::GetAgents().find(loop_id)->second;
        int new_method = agent->doLearning(loop_id, RLAgentFactory::GetTimesteps().at(loop_id), reward_signal);
        return new_method;
    }
}

RLAgent* RLAgentFactory::create_agent(const std::string& loop_id, int agent_type, int states, int actions, int offset = 0) {
    RLAgent *agent = nullptr;
    std::cout << "We got here again 1" << std::endl;
    int new_type = agent_type - offset;

    switch (new_type) {
        case (0): // Q-Learner Old
            std::cout << "We got here again 2" << std::endl;
            agent = new QLearnerOld(loop_id, states, actions);
            break;
        //case (1): // SARSA-Learner Old
        //    agent = new SarsaLearnerOld();
        //    break;
        default:
            std::cout << "Reinforcement Learning: Unknown agent type specified in options json: " << agent_type << std::endl;
    }

    return agent;
}

std::unordered_map<std::string, int>& RLAgentFactory::GetTimesteps() {
    static auto* timesteps = new std::unordered_map<std::string, int>();
    return *timesteps;
}

std::unordered_map<std::string, RLAgent*>& RLAgentFactory::GetAgents() {
    static auto* agents = new std::unordered_map<std::string, RLAgent*>();
    return *agents;
}