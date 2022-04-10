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
        Agent(num_states, num_actions, "SARSA Learner")
{
    // Initialize first dimension of table
    q_table = new double *[state_space];

    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    // Initialize values of table
    for (int a = 0; a < state_space; a++)
    {
        for (int s = 0; s < action_space; s++) {
            q_table[s][a] = 0.0f;
        }
    }

    set_table(q_table);
}

// private
void SARSALearner::update(int next_state, int next_action, double reward_value)
{
    q_table[current_state][next_action] += alpha * (reward_value + gamma * Q(next_state, next_state) - Q(current_state, next_state));
}
