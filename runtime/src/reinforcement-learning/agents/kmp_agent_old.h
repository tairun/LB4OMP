// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <string>
#include <utility>
#include "kmp_rl_info.h"
#include "kmp_agent.h"


class AgentOld : public Agent {
public:
    RLInfo* agent_data{}; // Saving the state of the agent between timesteps

    explicit AgentOld(int num_states, int num_actions, std::string agentName) :
             Agent(num_states, num_actions, std::move(agentName))
    {
        std::cout << "[AgentOld::AgentOld] Hello there from constructor ..." << std::endl;
        std::cout << "[AgentOld::AgentOld] Value of 'alpha' from base class: " << Agent::alpha << std::endl;
        std::cout << "[AgentOld::AgentOld] Address of 'agent_data' variable: " << agent_data << std::endl;

        agent_data = new RLInfo(num_states, num_actions);

        agent_data->alpha = Agent::alpha;
        agent_data->gamma = Agent::gamma;
        agent_data->reward_input = Agent::reward_input;

        std::cout << "[AgentOld::AgentOld] Constructor done. Bye!" << std::endl;
    }

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    int step(int episode, int timestep, LoopData* stats) override = 0;

private:
    void update(int next_state, int next_action, double reward_value) override = 0;
};
