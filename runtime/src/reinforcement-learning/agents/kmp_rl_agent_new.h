#pragma once

#include <string>

class RLAgentNew : public RLAgent {
public:
    RLAgentNew(int numStates, int numActions) : RLAgent(numStates, numActions),
                                                state(0),
                                                trialstate(0),
                                                lowTime(-99.0),
                                                highTime(-999.0),
                                                bestqvalue(0.0),
                                                alpha(0.6),
                                                gamma(0.6)
    {
        count = new int[states];
        qvalue = new double *[states];

        for (int i = 0; i < states; i++) {
            qvalue[i] = new double[actions];
        }

        for (int s = 0; s < states; s++)
            for (int a = 0; a < actions; a++) {
                count[a] = 0;
                qvalue[s][a] = -299.0;
            }

        if (std::getenv("KMP_RL_ALPHA") != NULL) {
            alpha = std::stod(std::getenv("KMP_RL_ALPHA"));
        } else {
            std::cout << "Couldn't read ALPHA from env." << std::endl;
        }

        if (std::getenv("KMP_RL_GAMMA") != NULL) {
            gamma = std::stod(std::getenv("KMP_RL_GAMMA"));
        } else {
            std::cout << "Couldn't read GAMMA from env." << std::endl;
        }
    }

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    int doLearning(int timestep, double reward_signal) override = 0;

private:

protected:
    int state;
    int trialstate;
    int *count;
    double lowTime, highTime;
    double **qvalue;
    double bestqvalue;

    double alpha;
    double gamma;
};
