#pragma once

#include <iostream>

/* Struct to manage data of the reinforcement learning agent */
class RLInfo {
public:
    int state;
    int trialstate;
    int *count;
    double lowTime, highTime;
    double **qvalue;
    double bestqvalue;

    double alpha;
    double gamma;

    RLInfo(int states, int actions) : state(0),
                                      trialstate(0),
                                      lowTime(-99.0),
                                      highTime(-999.0),
                                      bestqvalue(0.0),
                                      alpha(0.6),
                                      gamma(0.0)
    {
        std::cout << "We got here again 4" << std::endl;
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

        std::cout << "We got here again 4.5" << std::endl;

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

        std::cout << "We got here again 5" << std::endl;
    }

private:

};
