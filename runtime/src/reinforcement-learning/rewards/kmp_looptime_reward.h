// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include "kmp_loopdata.h"
#include "../agents/kmp_agent.h"

#pragma once

class Agent;

class LooptimeReward : public BaseReward {
public:
  double reward(LoopData* stats, Agent* agent) override;
};
