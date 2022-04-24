// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <unordered_map>

#pragma once


enum PolicyType
{
    EXPLORE_FIRST = 0,
    EPSILON_GREEDY = 1,
    SOFTMAX = 2
};

static std::unordered_map<std::string, PolicyType> PolicyTable = {
        {"explore_first", PolicyType::EXPLORE_FIRST},
        {"epsilon_greedy", PolicyType::EPSILON_GREEDY},
        {"softmax", PolicyType::SOFTMAX}
};

static std::unordered_map<int, std::string> PolicyLookup = {
        {PolicyType::EXPLORE_FIRST, "explore_first"},
        {PolicyType::EPSILON_GREEDY, "epsilon_greedy"},
        {PolicyType::SOFTMAX, "softmax"}
};
