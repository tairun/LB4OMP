#pragma once

#include "kmp_base_init.h"


/*
 * This class implements an initializer for the tabular data structures of the reinforcement learning agents.
 *
 * */
class ZeroInit : public BaseInit
{
private:
    ZeroInit() = default;
    ~ZeroInit() = default;

public:
    static void init(int* data, int size);
    static void init(double* data, int size);
    static void init(double** data, int num_actions, int num_states);
};