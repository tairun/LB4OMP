// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include "kmp_explore_first_policy.h"
#include "reinforcement-learning/utils/utils.h"
#include "reinforcement-learning/agents/kmp_agent.h"


int ExploreFirstPolicy::policy(int episode, int timestep, Agent* agent)
{
    int next_action;

    if (timestep < (agent->get_state_space() * agent->get_action_space()))
    // Try all actions
    {
#if (RL_DEBUG > 1)
        std::cout << "[ExploreFirstPolicy::policy] Exploring!" << std::endl;
#endif
        next_action = timestep % agent->get_action_space();
    }
    else
    // Greedy policy
    {
#if (RL_DEBUG > 1)
        std::cout << "[ExploreFirstPolicy::policy] Exploiting!" << std::endl;
#endif
        next_action = argmax(*agent->get_table(), agent->get_current_state(), agent->get_action_space());
    }

    return next_action;
}
