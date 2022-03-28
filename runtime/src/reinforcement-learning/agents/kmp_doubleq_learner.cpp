#include <random>

#include "kmp_rl_agent.h"
#include "kmp_doubleq_learner.h"


// public
DoubleQLearner::DoubleQLearner(int num_states, int num_actions) :
                RLAgent(num_states, num_actions, "DoubleQ Learner")
{
    // Initialize first dimension of table
    q_table_a   = new double *[state_space];
    q_table_b   = new double *[state_space];
    q_table_sum = new double *[state_space];

    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table_a[i]   = new double[action_space];
        q_table_b[i]   = new double[action_space];
        q_table_sum[i] = new double[action_space];
    }

    // Initialize values of table
    for (int a = 0; a < state_space; a++)
        for (int s = 0; s < action_space; s++) {
            q_table_a[s][a]   = 0.0f;
            q_table_b[s][a]   = 0.0f;
            q_table_sum[s][a] = 0.0f;
        }

    set_table(q_table_sum);
}

// private
void DoubleQLearner::update(int next_state, int next_action, double reward_value)
{
    std::default_random_engine re(time(0));
    std::uniform_real_distribution<double> uniform(0, 1);
    double updateA = uniform(re);

    if (updateA > 0.5) // Update table A or B with probability of 0.5
    {
        int bestIndex = arg_max(q_table_a, next_state);
        q_table_a[current_state][next_state] += alpha * (reward_value + gamma * q_table_b[next_state][bestIndex] - q_table_a[current_state][next_state]);
    }
    else
    {
        int bestIndex = arg_max(q_table_a, next_state);
        q_table_b[current_state][next_state] += alpha * (reward_value + gamma * q_table_a[next_state][bestIndex] - q_table_b[current_state][next_state]);
    }

    q_table_sum[current_state][next_state] = q_table_a[current_state][next_state] + q_table_b[current_state][next_state]; // Update the combined table (sum) to find best action in next step
}
