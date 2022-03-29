// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <iostream>


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

        // Read learning rate from env
        if (std::getenv("KMP_RL_ALPHA") != nullptr) {
           alpha = std::stod(std::getenv("KMP_RL_ALPHA"));
        } else {
            std::cout << "Couldn't read ALPHA from env." << std::endl;
        }

        // Read discount factor from env
        if (std::getenv("KMP_RL_GAMMA") != nullptr) {
            gamma = std::stod(std::getenv("KMP_RL_GAMMA"));
        } else {
            std::cout << "Couldn't read GAMMA from env." << std::endl;
        }

        // Read learning rate from env
        if (std::getenv("KMP_RL_REWARD") != nullptr) {
            reward_input = std::getenv("KMP_RL_REWARD");
        } else {
            std::cout << "Couldn't read REWARD from env." << std::endl;
        }
    }

private:

};
