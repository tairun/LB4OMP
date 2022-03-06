#pragma once

#include <string>
#include <utility>
#include "kmp_rl_info.h"
#include "kmp_rl_agent.h"


class RLAgentOld : public RLAgent {
public:
    RLAgentOld(int numStates, int numActions, std::string agentName) : RLAgent(numStates, numActions, std::move(agentName)) {

    }

    RLInfo* agent_data{}; // Saving the state of the agent between timesteps

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    int step(int timestep, LoopData* stats) override = 0;

private:

protected:

};
