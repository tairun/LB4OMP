#include <algorithm>
#include <ctime>
#include <random>

#include "kmp_sarsa_learner.h"

// public
SARSALearner::SARSALearner(int num_states, int num_actions) :
              RLAgent(num_states, num_actions, "SARSA Learner", q_table)
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

    alpha = read_env_double("KMP_RL_ALPHA");     // Read learning rate from env
    gamma = read_env_double("KMP_RL_GAMMA");     // Read discount factor from env
    epsilon = read_env_double("KMP_RL_EPSILON"); // Read exploration rate from env
}

// private
void SARSALearner::update(int next_state, int next_action, double reward_value)
{
    q_table[current_state][next_state] += alpha * (reward_value + gamma * q_table[next_state][next_state] - q_table[current_state][next_state]);
}
