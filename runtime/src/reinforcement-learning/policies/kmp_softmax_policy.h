//  ************************* Reinforcement Learning Extension ***********************************
//  * June 2022                                                                                  *
//  * Master Thesis                                                                              *
//  * Luc Kury, <luc.kury@unibas.ch>                                                             *
//  * University of Basel, Switzerland                                                           *
//  **********************************************************************************************
//  * INFORMATION:                                                                               *
//  * ------------                                                                               *
//  * The "Softmax" policy assigns each action a probability and selects the next actions        *
//  * according to the highest one.                                                              *
//  *                                                                                            *
//  * Environment variables:                                                                     *
//  *     (none)                                                                                 *
//  **********************************************************************************************

#pragma once

#include "kmp_base_policy.h"
#include "../agents/kmp_agent.h"


class SoftmaxPolicy : public BasePolicy
{
public:
    int policy(int episode, int timestep, Agent* agent) override;
};
