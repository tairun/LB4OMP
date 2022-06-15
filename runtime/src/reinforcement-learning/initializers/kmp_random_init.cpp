// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include <random>
#include "kmp_random_init.h"


RandomInit::RandomInit(double upper_bound, double lower_bound) : upper{upper_bound}, lower{lower_bound}
{
}

double RandomInit::get_double() const {
    static std::uniform_real_distribution<double> unif(lower, upper);
    std::default_random_engine re(defaults::SEED);
    return unif(re);
}

void RandomInit::init(int* data, int size)
{
    data = new int[size];

    for (int i = 0; i < size; i++)
    {
        data[i] = 0;
    }
}

void RandomInit::init(double* data, int size)
{
    data = new double[size];

    for (int i = 0; i < size; i++)
    {
        data[i] = get_double();
    }
}

void RandomInit::init(double **data, int num_states, int num_actions)
{
    data = new double*[num_states];

    for (int i = 0; i < num_states; i++) {
        data[i] = new double[num_actions];
    }

    for (int s = 0; s < num_states; s++)
    {
        for (int a = 0; a < num_actions; a++)
            data[s][a] = get_double();
    }
}
