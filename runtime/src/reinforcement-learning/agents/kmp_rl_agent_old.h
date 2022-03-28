#pragma once

#include <string>
#include <utility>
#include "kmp_rl_info.h"
#include "kmp_rl_agent.h"


class RLAgentOld : public RLAgent {
public:
    explicit RLAgentOld(int num_states, int num_actions, std::string agentName) :
             RLAgent(num_states, num_actions, std::move(agentName)) {

    }

    RLInfo* agent_data{}; // Saving the state of the agent between timesteps

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    int step(int episode, int timestep, LoopData* stats) override = 0;

private:
    void update(int next_state, int next_action, double reward_value) override = 0;

protected:

};

