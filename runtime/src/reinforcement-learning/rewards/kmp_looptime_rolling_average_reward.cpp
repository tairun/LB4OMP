// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include <numeric>
#include "kmp_loopdata.h"
#include "kmp_looptime_rolling_average_reward.h"
#include "reinforcement-learning/agents/kmp_agent.h"


double LooptimeRollingAverageReward::reward(LoopData* stats, Agent* agent) {
#if (RL_DEBUG > 1)
    std::cout << "[LooptimeRollingAverageReward::reward] Getting reward ..." << std::endl;
#endif
    static std::vector<double> avgs;
    double reward{0};

    if (avgs.size() >= agent->get_window())
    {
        avgs.pop_back();
    }

    avgs.insert(avgs.begin(), stats->cTime);
    double sum = std::accumulate(avgs.begin(), avgs.end(), 0.0);
    double avg = sum / avgs.size();

#if (RL_DEBUG > 0)
    std::cout << "[LooptimeRollingAverageReward::reward] Size: " << avgs.size() << ", Average: " << avg << std::endl;
#endif
    // Good case
    if ((stats->cTime) <= avg) // We choose <= as comparator to be optimistic (equally fast is good also)
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeRollingAverageReward::reward] Good!" << std::endl;
#endif
        reward = agent->get_reward_num()[0]; // by default: 0.0
    }
    else
    // Bad case
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeRollingAverageReward::reward] Bad!" << std::endl;
#endif
        reward = agent->get_reward_num()[1]; // by default: -2.0
    }

    return reward;
};
