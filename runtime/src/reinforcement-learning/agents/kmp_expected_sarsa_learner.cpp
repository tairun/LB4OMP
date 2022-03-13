#include <random>
#include <algorithm>
#include "kmp_expected_sarsa_learner.h"

// public
ExpectedSARSALearner::ExpectedSARSALearner(int numStates, int numActions) :
                      RLAgent(numStates, numActions, "SARSA Learner", q_table)
{
    count = new int[state_space];
    q_table = new double *[state_space];

    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    for (int s = 0; s < state_space; s++)
        for (int a = 0; a < action_space; a++) {
            count[a] = 0;
            q_table[s][a] = 0.0;
        }
}

// private
void ExpectedSARSALearner::update(int next_state, int next_action, double reward_value)
{
    q_table[current_state][next_state] += alpha * (reward_value + gamma * q_table[next_state][next_state] - q_table[current_state][next_state]);
}
