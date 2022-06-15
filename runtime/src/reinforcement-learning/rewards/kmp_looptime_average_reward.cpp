// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include "kmp_loopdata.h"
#include "kmp_looptime_average_reward.h"
#include "reinforcement-learning/agents/kmp_agent.h"


double LooptimeAverageReward::reward(LoopData* stats, Agent* agent) {
#if (RL_DEBUG > 1)
    std::cout << "[LooptimeAverageReward::reward] Getting reward ..." << std::endl;
#endif
    static int count{0};
    static double avg{0.0f};
    double reward{0};
    count++;

#if (RL_DEBUG > 0)
    std::cout << "[LooptimeAverageReward::reward] Count: " << count << ", Average: " << avg << std::endl;
#endif
    // Good case
    if ((stats->cTime) <= avg) // We choose <= as comparator to be optimistic (equally fast is good also)
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeAverageReward::reward] Good!" << std::endl;
#endif
        reward = agent->get_reward_num()[0]; // by default: 0.0
    }
    else
    // Bad case
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeAverageReward::reward] Bad!" << std::endl;
#endif
        reward = agent->get_reward_num()[1]; // by default: -2.0
    }

    avg = ((count - 1) * avg + stats->cTime) / count;
    return reward;
};
