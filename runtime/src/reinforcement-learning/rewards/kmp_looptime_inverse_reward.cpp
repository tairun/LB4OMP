// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include "kmp_loopdata.h"
#include "kmp_looptime_inverse_reward.h"
#include "../agents/kmp_agent.h"

double LooptimeInverseReward::reward(LoopData* stats, Agent* agent) {
#if (RL_DEBUG > 1)
    std::cout << "[LooptimeInverseReward::reward] Getting reward ..." << std::endl;
#endif

    return (1/stats->cTime) * defaults::INVERSE_REWARD_MULT; // TODO@kurluc00: Read multiplier from env
};
