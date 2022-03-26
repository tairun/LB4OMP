// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include "reinforcement-learning/agents/kmp_rl_agent.h"


class BasePolicy
{
protected:
    virtual int policy(int episode, int timestep, RLAgent& agent) = 0;
};
