// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include <random>
#include <iostream>
#include "kmp_random_init.h"


RandomInit::RandomInit(double upper_bound, double lower_bound) : upper{upper_bound}, lower{lower_bound}
{
    std::cout << "[RandomInit::RandomInit] Hi from Constructor ..." << std::endl;
}

double RandomInit::get_double() const {
    //std::cout << "[RandomInit::get_double] Before unif ..." << std::endl;
    static std::uniform_real_distribution<double> unif(lower, upper);
    //std::cout << "[RandomInit::get_double] Before engine ..." << std::endl;
    static std::default_random_engine re(defaults::SEED);
    //std::cout << "[RandomInit::get_double] Before return ..." << std::endl;
    double the_num = unif(re);
    std::cout << "[RandomInit::get_double] The number is  ... " << the_num << std::endl;
    return the_num;
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
