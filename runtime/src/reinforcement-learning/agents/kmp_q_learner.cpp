#include <algorithm>
#include <ctime>
#include <random>

#include "kmp_q_learner.h"

// public
QLearner::QLearner(int num_states, int num_actions) :
          RLAgent(num_states, num_actions, "Q Learner", q_table)
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
}

// private
void QLearner::update(int next_state, int next_action, double reward_value)
{
    int best_action = arg_max(q_table, next_state);
    q_table[current_state][current_action] += alpha * (reward_value + gamma * q_table[next_state][best_action] - q_table[current_state][current_action]);
}
