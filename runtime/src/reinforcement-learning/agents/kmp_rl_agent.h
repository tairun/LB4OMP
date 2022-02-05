#pragma once

#include <string>

#include "kmp_rl_info.h"

class RLAgent {
public:
    RLAgent(int states, int actions) {
        states = states;
        actions = actions;
    }

    std::unordered_map<std::string, RLInfo*> agent_data{}; // Saving the state of the agent between timesteps

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int doLearning(std::string loop_id, int timestep, double reward_signal) = 0;

private:
    int states{};
    int actions{};
};
