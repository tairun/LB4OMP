// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include "kmp_base_policy.h"


class ExploreFirstPolicy : public BasePolicy
{
public:
    int policy(int episode, int timestep, Agent& agent) override;
};
