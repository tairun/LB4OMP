// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <iostream>

#include "kmp_explore_first_policy.h"


int ExploreFirstPolicy::policy(int episode, int timestep, Agent* agent)
{
    int i, action, action_max;

    std::cout << "[ExploreFirstPolicy::policy] Threshold: " << agent->get_state_space() * agent->get_action_space() << ", Timestep: " << timestep << std::endl;

    if (timestep < (agent->get_state_space() * agent->get_action_space()))
    // Try all actions
    {
        std::cout << "[ExploreFirstPolicy::policy] Exploring!" << std::endl;
        action = timestep % agent->get_action_space();
    }
    else
    // Greedy policy
    {
        std::cout << "[ExploreFirstPolicy::policy] Exploiting!" << std::endl;
        action_max = 0;
        for (i = 0; i < agent->get_action_space(); i++)
            if (agent->get_table()[agent->get_current_state()][i] >
                agent->get_table()[agent->get_current_state()][action_max])
                action_max = i;
        action = action_max;
    }

    return action;
}
