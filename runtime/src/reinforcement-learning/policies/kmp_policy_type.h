// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

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