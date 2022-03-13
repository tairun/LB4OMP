#include <algorithm>
#include <random>

#include "kmp_qv_learner.h"

// public
QVLearner::QVLearner(int num_states, int num_actions) :
           RLAgent(num_states, num_actions, "QV Learner", q_table)
{
    count = new int[state_space];
    q_table = new double *[state_space];
    v_table = new double *[state_space];

    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
        v_table[i] = new double[action_space];
    }

    for (int s = 0; s < state_space; s++)
        for (int a = 0; a < action_space; a++) {
            count[a] = 0;
            q_table[s][a] = 0.0f;
            v_table[s][a] = 0.0f;
        }
}

// private
void QVLearner::update(int next_state, int next_action, double reward_value)
{
    std::uniform_real_distribution<double> uniform1(0, 1);
    std::default_random_engine re;
    double updateA = uniform1(re);

    if (updateA > 0.5) // Update table A or B with probability of 0.5
    {
        int bestIndex = arg_max(qTableA, nextState);
        qTableA[current_state][nextState] += alpha * (rewardValue + gamma * qTableB[nextState][bestIndex] - qTableA[current_state][nextState]);
    }
    else
    {
        int bestIndex = arg_max(qTableA, nextState);
        qTableB[current_state][nextState] += alpha * (rewardValue + gamma * qTableA[nextState][bestIndex] - qTableB[current_state][nextState]);
    }

    qTableSum[current_state][nextState] = qTableA[current_state][nextState] + qTableB[current_state][nextState]; // Update the combined table (sum) to find best action in next step
}
