#include "kmp_epsilon_greedy_policy.h"
#include "../agents/kmp_rl_agent.h"

int EpsilonGreedyPolicy::policy(int episode, int timestep, RLAgent& agent)
{
    std::default_random_engine re(time(nullptr));
    std::uniform_real_distribution<double> uniform(0, 1);

    // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
    if (uniform(re) < agent.get_epsilon())
        // Explore (random action)
    {
        int next_action = agent.sample_action(); // Chooses action (which is equal to the next state)
        return next_action;
    }
    else
        // Exploit (previous knowledge)
    {
        int maxQ = -9999;
        std::vector<int> action_candidates;

        // Evaluate Q-Table for action with highest Q-Value
        for (int i = 0; i < agent.get_action_space(); i++)
        {
            if (agent.get_table()[agent.get_current_state()][i] >= maxQ)
            {
                action_candidates.push_back(i);
            }
        }

        // Selects a random action if multiple actions have the same Q-Value
        std::uniform_int_distribution<int> uniform2(0, (int)action_candidates.size());
        int next_action_index = uniform2(re);
        int next_action = action_candidates[next_action_index];

        return next_action;
    }
}
