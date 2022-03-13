#include <algorithm>
#include <random>

#include "kmp_qv_learner.h"

// public
QVLearner::QVLearner(int num_states, int num_actions) :
           RLAgent(num_states, num_actions, "QV Learner", q_table)
{
    // Initialize first dimension of table
    v_table = new double[state_space];
    q_table = new double *[state_space];

    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    // Initialize values of table
    for (int s = 0; s < state_space; s++)
    {
        v_table[s] = 0.0f;
        for (int a = 0; a < action_space; a++)
            q_table[s][a] = 0.0f;
    }
}

// private
void QVLearner::update(int next_state, int next_action, double reward_value)
{
    v_table[current_state] += alpha * (reward_value + (gamma * v_table[next_state] - v_table[current_state]));
    q_table[current_state][next_action] += alpha * (reward_value + gamma * v_table[next_state] - q(current_state, next_action));

    //qTableSum[current_state][nextState] = qTableA[current_state][nextState] + qTableB[current_state][nextState]; // Update the combined table (sum) to find best action in next step
}
