// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include "kmp_loopdata.h"
#include "kmp_base_reward.h"

#pragma once

class Agent;

class LooptimeInverseReward : public BaseReward
{
public:
  double reward(LoopData* stats, Agent* agent) override;
};
