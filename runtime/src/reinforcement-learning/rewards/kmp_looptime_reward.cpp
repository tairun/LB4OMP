// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include "kmp_loopdata.h"
#include "kmp_looptime_reward.h"
#include "reinforcement-learning/agents/kmp_agent.h"


double LooptimeReward::reward(LoopData* stats, Agent* agent) {
#if (RL_DEBUG > 1)
    std::cout << "[LooptimeReward::reward] Getting reward ..." << std::endl;
#endif
    double reward_signal = stats->cTime;
    double low = agent->get_low();
    double high = agent->get_high();
#if (RL_DEBUG > 0)
    std::cout << "[LooptimeReward::reward] High: " << high << ", Low: " << low << ", Reward: " << reward_signal << std::endl;
#endif
    // Good case
    if ((reward_signal) < low)
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeReward::reward] Good!" << std::endl;
#endif
        agent->set_low(reward_signal);
        return agent->get_reward_num()[0]; // by default: 0.0
    }
    // Neutral case
    if ((reward_signal > low) && (reward_signal < high))
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeReward::reward] Neutral." << std::endl;
#endif
        return agent->get_reward_num()[1]; // by default: -2.0
    }
    // Bad case
    if (reward_signal > high)
    {
#if (RL_DEBUG > 1)
        std::cout << "[LooptimeReward::reward] Bad!" << std::endl;
#endif
        agent->set_high(reward_signal);
        return agent->get_reward_num()[2]; // by default: -4.0
    }
};
