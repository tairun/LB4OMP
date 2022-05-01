// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <random>

#include "kmp_agent.h"
#include "kmp_r_learner.h"


// public
RLearner::RLearner(int num_states, int num_actions) :
        Agent(num_states, num_actions, "R-Learner")
{
    // Initialize first dimension of table
    q_table = new double *[state_space];

    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    // Initialize values of table
    for (int s = 0; s < state_space; s++)
        for (int a = 0; a < action_space; a++)
            q_table[s][a] = 0.0f;

    set_table(q_table);
}

// private
void RLearner::update(int next_state, int next_action, double reward_value)
{
    // TODO@kurluc00: Implement
}
