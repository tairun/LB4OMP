// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <iostream>

#include "../utils/utils.h"


/* Struct to manage data of the reinforcement learning agent */
class RLInfo
{
public:
    int state;
    int trialstate;
    int *count;
    double low, high;
    double **qvalue;
    double bestqvalue;

    double alpha;
    double gamma;

    std::string reward_input;

    RLInfo(int states, int actions) : state(0),
                                      trialstate(0),
                                      low(-99.0),
                                      high(-999.0),
                                      bestqvalue(0.0),
                                      alpha(0.6),
                                      gamma(0.6),
                                      reward_input("looptime")
    {
        count = new int[states];
        qvalue = new double *[states];

        for (int i = 0; i < states; i++) {
            qvalue[i] = new double[actions];
        }

        for (int s = 0; s < states; s++)
            for (int a = 0; a < actions; a++) {
                count[a] = 0;
                qvalue[s][a] = 0.0;
            }

        read_env_double("KMP_RL_ALPHA", alpha);
        read_env_double("KMP_RL_GAMMA", gamma);
        read_env_string("KMP_RL_REWARD", reward_input);
    }

private:

};
