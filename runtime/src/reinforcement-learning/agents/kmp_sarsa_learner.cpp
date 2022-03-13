#include <algorithm>
#include <ctime>
#include <random>

#include "kmp_sarsa_learner.h"

// public
SARSALearner::SARSALearner(int num_states, int num_actions) :
              RLAgent(num_states, num_actions, "SARSA Learner", q_table)
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
}

// private
void SARSALearner::update(int next_state, int next_action, double reward_value)
{
    q_table[current_state][next_action] += alpha * (reward_value + gamma * Q(next_state, next_state) - Q(current_state, next_state));
}
