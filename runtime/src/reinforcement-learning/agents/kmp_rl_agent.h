#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "../kmp_loopdata.h"


class RLAgent {
public:
    RLAgent(int num_states, int num_actions, std::string agent_name, double** ref_table) : state_space(num_states),
                                                                                       action_space(num_actions),
                                                                                       name(std::move(agent_name)),
                                                                                       table(ref_table)
    {
        count = new int[state_space];

        alpha   = read_env_double("KMP_RL_ALPHA");     // Read learning rate from env
        gamma   = read_env_double("KMP_RL_GAMMA");     // Read discount factor from env
        epsilon = read_env_double("KMP_RL_EPSILON"); // Read exploration rate from env
        //lamdba  = read_env_double("KMP_RL_LAMBDA");           // Read discount factor from env
        //tau     = read_env_double("KMP_RL_TAU");          // Read exploration rate from env
        reward_input = read_env_string("KMP_RL_REWARD");
        alpha_decay_rate = read_env_double("KMP_RL_ALPHA_DECAY");

        std::cout << "[Reinforcement Learning] Configuring agent as: " << name << std::endl;
        std::cout << "[Reinforcement Learning] Using reward signal: " << reward_input << std::endl;
    }

    /* Takes reward and performs the learning process. Returns the prediction for the next action from the agent. */
    int step(int timestep, LoopData* stats)
    {
        int next_action, next_state;
        double reward_value = reward(stats);           // Convert the reward signal into the actual reward value
        next_action = policy(table);                  // Predict the next action according to the policy and Q-Values
        next_state = next_action;                      // In our scenario the next action and desired state is the same
        update(next_state, next_action, reward_value); // Update the Q-Values based on the learning algorithm

        current_state = next_state;                    // Update the state in the class
        current_action = next_action;                  // Update the action in the class

        // Decay learning rate if the value is not zero
        if ((bool)alpha_decay_rate)
        {
            alpha = alpha * alpha_decay_rate;
        }

        return next_state;
    }

private:
    double** table; // Pointer to table to lookup the best next action

    /* The policy chooses an action according to the learned experience of the agent. */
    /* Implements the Epsilon-Greedy action selection. */
    int policy(double** ref_table)
    {
        std::default_random_engine re(time(0));
        std::uniform_real_distribution<double> uniform(0, 1);

        // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
        if (uniform(re) < epsilon) // Explore (random action)
        {
            int next_action = sample_action(); // Chooses action (which is equal to the next state)
            return next_action;
        }
        else // Exploit (previous knowledge)
        {
            int maxQ = -9999;
            std::vector<int> action_candidates;

            // Evaluate Q-Table for action with highest Q-Value
            for (int i = 0; i < action_space; i++)
            {
                if (ref_table[current_state][i] >= maxQ)
                {
                    action_candidates.push_back(i);
                }
            }

            // Selects a random action if multiple actions have the same Q-Value
            std::uniform_int_distribution<int> uniform2(0, (int)action_candidates.size());
            int next_state_index = uniform2(re);
            int next_state = action_candidates[next_state_index];

            return next_state;
        }
    }

protected:
    int state_space;       // Amount of states in the environment
    int action_space;      // Amount of action available to the agent
    int current_state{0};  // We always start with static scheduling method as initial state (it's the first method from the portfolio)
    int current_action{0}; // Set action also to selecting the static scheduling method

    double alpha{0.85f};   // Learning rate
    double gamma{0.95f};   // Discount factor
    double epsilon{0.10f}; // Exploration rate
    double lamdba{0.00f};  // QV-Learning specific
    double tau{0.00f};     // QV-Learning specific
    double low{-99.0f}, high{-999.0f};
    double alpha_decay_rate{0.0f};

    std::string name;
    std::string reward_input{"looptime"};

    /* Updates the internal values of the agent. */
    virtual void update(int next_state, int next_action, double reward_value) = 0;

    /****************************************************************************/

    /* Reads the environment variable with the name 'var_name' and parses it as a string */
    static std::string read_env_string(const char* var_name)
    {
        if (std::getenv(var_name) != nullptr)
        {
            return std::string(std::getenv(var_name));
        }
        else
        {
            std::cout << "[Reinforcement Learning] Couldn't read '" << var_name << "' from env." << std::endl;
        }
    }

    /* Reads the environment variable with the name 'var_name' and parses it as a double */
    static double read_env_double(const char* var_name)
    {
        if (std::getenv(var_name) != nullptr)
        {
            return std::stod(std::getenv(var_name));
        }
        else
        {
            std::cout << "[Reinforcement Learning] Couldn't read '" << var_name << "' from env." << std::endl;
        }
    }

    /* Reads the reward signal variable and return the  */
    double get_reward_signal(LoopData* stats)
    {
        double reward_signal = 0;

        if (reward_input == "looptime")
        {
            reward_signal = stats->cTime;
        }
        else if (reward_input == "loadimbalance")
        {
            reward_signal = stats->cLB;
        }
        else if (reward_input == "robustness")
        {
            std::cout << "[Reinforcement Learning] Not yet implemented: " << reward_input << std::endl;
            reward_signal = stats->cTime;
        }
        else
        {
            std::cout << "[Reinforcement Learning] Invalid reward signal specified in env: " << reward_input << std::endl;
        }

        return reward_signal;
    }

    /* Transforms the reward signal into the reward value */
    double reward(LoopData* stats)
    {
        double reward_signal = get_reward_signal(stats);

        // Good case
        if ((reward_signal) < low)
        {
            low = reward_signal;
            return 2.0;
        }
        // Neutral case
        if ((reward_signal > low) && (reward_signal < high))
        {
            return 0.0;
        }
        // Bad case
        if (reward_signal > high)
        {
            high = reward_signal;
            return -2.0;
        }
    }

    /*
     * Chooses a random action from the action space uniformly.
     * */
    int sample_action() const
    {
        std::default_random_engine re(time(0));
        std::uniform_int_distribution<int> uniform(0, action_space);

        return uniform(re);
    }

    /*
     * Searches for the best action (index) for a given state (using the Q-Values).
     * */
    int arg_max(double** ref_table, int next_state) const
    {
        int best_index = 0;
        double best_current = -9999;

        for (int i = 0; i < action_space; i++)
        {
            if (ref_table[next_state][i] > best_current)
            {
                best_current = ref_table[next_state][i];
                best_index = i;
            }
        }
        return best_index;
    }

    /*
     * Returns a pointer to the Q-Values (array) stored for a particular state.
     * */
    double* q(int state) {
        return table[state];
    }

    /*
 * Returns the Q-Value stored for a particular state-action pair.
 * */
    double q(int state, int action) {
        return table[state][action];
    }

    double sum(const double* array) const
    {
        double sum = 0;

        for (int i = 0; i < action_space; i++)
            sum += array[i];

        return sum;
    }
};
