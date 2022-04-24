// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <unordered_map>

#pragma once


enum RewardType
{
    LOOPTIME = 0,
    LOADIMBALANCE = 1,
    ROBUSTNESS = 2
};

static std::unordered_map<std::string, RewardType> RewardTable = {
        {"looptime", RewardType::LOOPTIME},
        {"loadimbalance", RewardType::LOADIMBALANCE},
        {"robustness", RewardType::ROBUSTNESS}
};

static std::unordered_map<int, std::string> RewardLookup = {
        {RewardType::LOOPTIME, "looptime"},
        {RewardType::LOADIMBALANCE, "loadimbalance"},
        {RewardType::ROBUSTNESS, "robustness",}
};
