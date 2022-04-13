// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <iostream>

#include "defaults.h"
#include "../utils/utils.h"


/* Struct to manage data of the reinforcement learning agent */
class RLInfo
{
public:
    int state{0};
    int trialstate{0};
    int *count;
    double low{-99.0f}, high{-999.0f};
    double **qvalue;
    double bestqvalue{0.0f};

    double alpha{defaults::ALPHA};
    double gamma{defaults::GAMMA};

    std::string reward_input{defaults::REWARD_INPUT};

    RLInfo(int states, int actions)
    {
        std::cout << "[RLInfo::RLInfo] Hello there from constructor ..." << std::endl;

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

        std::cout << "[RLInfo::RLInfo] Constructor done. Bye!" << std::endl;
    }

private:
    // empty
};
