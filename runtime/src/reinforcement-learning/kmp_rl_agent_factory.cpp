#include <string>
#include <iostream>

#include "kmp_agent_type.h"
#include "kmp_rl_agent_factory.h"
#include "agents/kmp_q_learner_old.h"
#include "agents/kmp_sarsa_learner_old.h"
#include "agents/kmp_agent_options.h"

int RLAgentFactory::rlAgentSearch(const std::string& loop_id, int agent_type, double reward_signal, int portfolio_size) {
    //TODO: Make print statement here (with thread ID)
    if (!rl_timesteps.count(loop_id)) {
        rl_timesteps.insert(std::make_pair(loop_id, 0));

        auto agent = create_agent(loop_id, agent_type, portfolio_size, portfolio_size, 0);
        agents.insert(std::make_pair(loop_id, agent));
        return 0;
    } else {
        auto agent = agents.find(loop_id)->second;
        int new_method = agent->doLearning(loop_id, rl_timesteps.at(loop_id), reward_signal);
        return new_method;
    }
}

RLAgent *RLAgentFactory::create_agent(const std::string& loop_id, int agent_type, int states, int actions, int offset = 0) {
    RLAgent *agent;

    int new_type = agent_type - offset;

    switch (new_type) {
        case (0): // Q-Learner Old
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
