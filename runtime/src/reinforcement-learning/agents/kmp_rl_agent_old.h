#pragma once

#include <string>

#include "kmp_rl_info.h"

class RLAgentOld {
public:
    RLAgentOld(int numStates, int numActions) : states(numStates), actions(numActions) {

    }

    RLInfo* agent_data; // Saving the state of the agent between timesteps

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int doLearning(const std::string& loop_id, int timestep, double reward_signal) = 0;

private:

protected:
    int states;
    int actions;
};
