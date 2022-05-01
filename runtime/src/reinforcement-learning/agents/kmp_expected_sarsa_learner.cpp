// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <random>

#include "kmp_agent.h"
#include "kmp_expected_sarsa_learner.h"


// public
ExpectedSARSALearner::ExpectedSARSALearner(int numStates, int numActions) :
        Agent(numStates, numActions, "ExpectedSARSA-Learner")
{
    // Initialize first dimension of table
    q_table = new double *[state_space];

    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    // Initialize values of table
    for (int s = 0; s < state_space; s++){
        for (int a = 0; a < action_space; a++) {
            q_table[s][a] = 0.0f;
        }
    }

    set_table(q_table);
}

// private
void ExpectedSARSALearner::update(int next_state, int next_action, double reward_value)
{
    int best_action = arg_max(q_table, next_state);
    double expected_return = (1 - epsilon) * Q(next_state, best_action) + (epsilon / action_space) * sum(Q(next_state), action_space);
    q_table[current_state][next_action] += alpha * (reward_value + gamma * expected_return - Q(current_state, next_action));
}
