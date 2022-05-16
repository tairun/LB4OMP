// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <unordered_map>

#pragma once


enum InitType
{
    ZERO       = 0,
    RANDOM     = 1,
    OPTIMISTIC = 2
};

static std::unordered_map<std::string, InitType> InitTable = {
        {"zero", InitType::ZERO},
        {"random", InitType::RANDOM},
        {"optimistic", InitType::OPTIMISTIC}
};

static std::unordered_map<int, std::string> InitLookup = {
        {InitType::ZERO, "zero"},
        {InitType::RANDOM, "random"},
        {InitType::OPTIMISTIC, "optimistic"}
};
