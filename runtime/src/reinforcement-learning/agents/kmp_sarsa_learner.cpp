// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <random>

#include "kmp_agent.h"
#include "kmp_sarsa_learner.h"


// public
SARSALearner::SARSALearner(int num_states, int num_actions) :
        Agent(num_states, num_actions, "SARSA-Learner")
{
    // Initialize first dimension of table
    pInit->init(q_table, state_space, action_space);
    set_table(q_table);
}

// private
void SARSALearner::update(int next_state, int next_action, double reward_value)
{
    q_table[current_state][next_action] += alpha * (reward_value + gamma * Q(next_state, next_state) - Q(current_state, next_state));
}
