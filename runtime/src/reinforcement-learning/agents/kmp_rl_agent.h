#pragma once

#include <string>
#include <iostream>

#include "../kmp_loopdata.h"

class RLAgent {
public:
    RLAgent(int numStates, int numActions) : states(numStates), actions(numActions) {
        if (std::getenv("KMP_RL_REWARD") != nullptr) {
            reward_input = std::getenv("KMP_RL_REWARD");
        } else {
            std::cout << "Couldn't read REWARD from env." << std::endl;
        }
    }

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int doLearning(int timestep, LoopData* data) = 0;

private:

protected:
    int states;
    int actions;
    std::string reward_input;
};
