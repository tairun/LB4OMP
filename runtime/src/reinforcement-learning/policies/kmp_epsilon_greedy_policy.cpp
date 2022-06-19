// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include <random>
#include "kmp_epsilon_greedy_policy.h"
#include "reinforcement-learning/agents/defaults.h"
#include "reinforcement-learning/agents/kmp_agent.h"


int EpsilonGreedyPolicy::policy(int episode, int timestep, Agent* agent)
{
    std::default_random_engine re(defaults::SEED);
    std::uniform_real_distribution<double> uniform(0, 1);
    int next_action;

    // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
    if (uniform(re) < agent->get_epsilon())
    // Explore (random action)
    {
#if (RL_DEBUG > 1)
        std::cout << "[EpsilonGreedyPolicy::policy] Exploring!" << std::endl;
#endif
        next_action = agent->sample_action(); // Chooses action (which is equal to the next state)
    }
    else
    // Exploit (previous knowledge)
    {
#if (RL_DEBUG > 1)
        std::cout << "[EpsilonGreedyPolicy::policy] Exploiting!" << std::endl;
#endif
        next_action = argmax(*agent->get_table(), agent->get_current_state(), agent->get_action_space());
    }
    return next_action;
}
