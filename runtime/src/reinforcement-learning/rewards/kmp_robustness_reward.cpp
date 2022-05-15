// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include "kmp_robustness_reward.h"
#include "kmp_loopdata.h"

#pragma once

double RobustnessReward::reward(LoopData* stats, Agent* agent) {
    if (stats->cTime <= agent->get_tau() * agent->get_low())
    {
        return agent->get_tau() * agent->get_low() - stats->cTime;
    }
    else
    {
        return -1.0f;
    }
};
