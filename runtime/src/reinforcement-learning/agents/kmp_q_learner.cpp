// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <random>

#include "kmp_agent.h"
#include "kmp_q_learner.h"


// public
QLearner::QLearner(int num_states, int num_actions) :
        Agent(num_states, num_actions, "Q-Learner")
{
    // Initialize first dimension of table
    pInit->init(q_table, state_space, action_space);
    set_table(q_table);
}

// private
void QLearner::update(int next_state, int next_action, double reward_value)
{
    int best_action = arg_max(q_table, next_state);
    q_table[current_state][current_action] += alpha * (reward_value + gamma * Q(next_state, best_action) - Q(current_state, current_action));
}
