// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include "kmp_base_policy.h"


class SoftmaxPolicy : public BasePolicy
{
public:
    int policy(double** ref_table) override;
};
