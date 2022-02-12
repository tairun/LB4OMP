#pragma once

#include <string>

class RLAgent {
public:
    RLAgent(int numStates, int numActions) : states(numStates), actions(numActions) {

    }

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int doLearning(int timestep, double reward_signal) = 0;

private:

protected:
    int states;
    int actions;
};
