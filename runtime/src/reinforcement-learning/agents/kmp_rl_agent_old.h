#pragma once

#include <string>

#include "kmp_rl_info.h"
#include "kmp_rl_agent.h"

class RLAgentOld : public RLAgent {
public:
    RLAgentOld(int numStates, int numActions) : RLAgent(numStates, numActions) {

    }

    RLInfo* agent_data{}; // Saving the state of the agent between timesteps

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    int doLearning(int timestep, double reward_signal) override = 0;

private:

protected:

};
