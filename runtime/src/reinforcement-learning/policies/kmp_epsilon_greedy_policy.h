// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include "kmp_base_policy.h"
#include "../agents/kmp_rl_agent.h"


class EpsilonGreedyPolicy : public BasePolicy
{
protected:
    int policy(int episode, int timestep, RLAgent& agent) override;
};
