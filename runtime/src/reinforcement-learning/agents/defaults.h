// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include "../rewards/kmp_reward_type.h"
#include "../initializers/kmp_init_type.h"
#include "../policies/kmp_policy_type.h"

#pragma once


namespace defaults {
    const double SEED                   = 420.69f;

    const double ALPHA                  = 0.85f;
    const double ALPHA_MIN              = 0.10f;
    const double ALPHA_DECAY_FACTOR     = 0.05f;
    const double GAMMA                  = 0.95f;
    const double EPSILON                = 0.90f;
    const double EPSILON_MIN            = 0.10f;
    const double EPSILON_DECAY_FACTOR   = 0.10f;

    const RewardType REWARD_TYPE        = RewardType::LOOPTIME;
    const InitType INIT_TYPE            = InitType::ZERO;
    const PolicyType POLICY_TYPE        = PolicyType::EXPLORE_FIRST;
}
