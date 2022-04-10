#pragma once

#include "kmp_base_init.h"


/*
 * This class implements an initializer for the tabular data structures of the reinforcement learning agents.
 *
 * */
class RandomInit : public BaseInit
{
public:
    void init(int* data, int size) override;
    void init(double* data, int size) override;
    void init(double** data, int num_actions, int num_states) override;
};
