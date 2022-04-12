// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include <string>

#include "../kmp_loopdata.h"
#include "../utils/utils.h"
#include "../initializers/kmp_base_init.h"
#include "../policies/kmp_base_policy.h"


class Agent {
public:
    Agent(int num_states, int num_actions, std::string agent_name) : state_space(num_states),
                                                                     action_space(num_actions),
                                                                     name(std::move(agent_name))
    {
        read_env_double("KMP_RL_ALPHA", alpha);     // Read learning rate from env
        read_env_double("KMP_RL_GAMMA", gamma);     // Read discount factor from env
        read_env_double("KMP_RL_EPSILON", epsilon); // Read exploration rate from env

        //read_env_double("KMP_RL_LAMBDA", lambda);
        //read_env_double("KMP_RL_TAU", tau);

        read_env_string("KMP_RL_INIT", init_input);
        read_env_string("KMP_RL_REWARD", reward_input);
        read_env_string("KMP_RL_POLICY", policy_input);

        read_env_double("KMP_RL_ALPHA_DECAY", alpha_decay_factor);
        read_env_double("KMP_RL_EPS_DECAY", epsilon_decay_factor);

        std::cout << "[Agent::Agent] Configuring agent as: " << name << std::endl;
        std::cout << "[Agent::Agent] Additional params: Initializer-->" << init_input << ", Reward-->" << reward_input << ", Policy-->" << policy_input << std::endl;
    }

    /*
     * Takes reward and performs the learning process. Returns the prediction for the next action from the agent.
     * */
    virtual int step(int episode, int timestep, LoopData* stats)
    {
        std::cout << "[Agent::step] Starting learning ..." << std::endl;
        int next_action, next_state;
        double reward_value = reward(stats);           // Convert the reward signal into the actual reward value
        next_action = policy(episode, timestep, table);           // Predict the next action according to the policy and Q-Values
        next_state = next_action;                      // In our scenario the next action and desired state is the same
        std::cout << "[Agent::update] Updating agent data ..." << std::endl;
        update(next_state, next_action, reward_value); // Update the Q-Values based on the learning algorithm

        current_state = next_state;                    // Update the state in the class
        current_action = next_action;                  // Update the action in the class

        // Decay
        alpha_decay(episode);
        epsilon_decay(episode);

        return next_action;
    }

    /*
    * Chooses a random action from the action space uniformly.
    * */
    int sample_action() const
    {
        std::default_random_engine re(seed); //TODO@kurluc00: Properly seed the random engine.
        std::uniform_int_distribution<int> uniform(0, action_space);

        return uniform(re);
    }

    // Getters
    double get_epsilon() const {
        return epsilon;
    }

    int get_state_space() const {
        return state_space;
    }

    int get_action_space() const {
        return action_space;
    }

    std::string get_init_input() const {
        return init_input;
    }

    std::string get_policy_input() const {
        return policy_input;
    }

    double** get_table() const {
        return table;
    }

    int get_current_state() const {
        return current_state;
    }

    void set_table(double** table_ref)
    {
        table = table_ref;
    }

    void set_initializer(BaseInit* init) {
        pInit = init;
    }

    void set_policy(BasePolicy* policy) {
        pPolicy = policy;
    }

private:
    double seed{420.69};     // Controls the seed for the number generators
    double** table{nullptr}; // Pointer to table to lookup the best next action

protected:
    BaseInit* pInit{nullptr};
    BasePolicy* pPolicy{nullptr};

    int state_space;       // Amount of states in the environment
    int action_space;      // Amount of action available to the agent
    int current_state{0};  // We always start with static scheduling method as initial state (it's the first method from the portfolio)
    int current_action{0}; // Set action also to selecting the static scheduling method

    double alpha{0.85f};        // Learning rate
    double alpha_min{0.10f};    // Learning rate
    double gamma{0.95f};        // Discount factor
    double epsilon{1.00f};      // Exploration rate
    double epsilon_min{0.10f};  // Exploration rate
    double lamdba{0.00f};       // QV-Learning specific
    double tau{0.00f};          // QV-Learning specific
    double low{-99.00f}, high{-999.00f};
    double alpha_decay_factor{0.90f};
    double epsilon_decay_factor{0.90f};

    std::string name;
    std::string init_input{"zero"};
    std::string reward_input{"looptime"};       // Default: looptime.       Options are: looptime, loadimbalance, robustness
    std::string policy_input{"explore_first"};  // Default: explore_first.  Options are: explore_first, epsilon_greedy, softmax

    /*----------------------------------------------------------------------------*/
    /*                            MEMBER FUNCTIONS                                */
    /*----------------------------------------------------------------------------*/

    /* The policy chooses an action according to the learned experience of the agent. */
    /* Implements the Epsilon-Greedy action selection. */
    virtual int policy(int episode, int timestep, double** ref_table)
    {
        std::cout << "[Agent::policy] Applying policy ..." << std::endl;

        std::default_random_engine re(seed);
        std::uniform_real_distribution<double> uniform(0, 1);

        // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
        if (uniform(re) < epsilon)
        // Explore (random action)
        {
            std::cout << "[Agent::policy] Exploring" << std::endl;
            int next_action = sample_action(); // Chooses action (which is equal to the next state)
            return next_action;
        }
        else
        // Exploit (previous knowledge)
        {
            std::cout << "[Agent::policy] Exploiting" << std::endl;
            double maxQ = -9999.99f;
            std::vector<int> action_candidates;

            // Evaluate Q-Table for action with highest Q-Value
            for (int i = 0; i < action_space; i++)
            {
                if (ref_table[current_state][i] > maxQ)
                {
                    action_candidates.clear();
                    action_candidates.push_back(i);
                    maxQ = ref_table[current_state][i];
                }
                else if (ref_table[current_state][i] == maxQ)
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

    /* Updates the internal values of the agent. */
    virtual void update(int next_state, int next_action, double reward_value) = 0;

    /*
     * Transforms the reward signal into the reward value.
     * */
    double reward(LoopData* stats)
    {
        std::cout << "[Agent::reward] Getting reward ..." << std::endl;

        //TODO@kurluc00: Explore negative vs. positive Rewards discussion for agents.
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
    double* Q(int state)
    {
        return table[state];
    }

    /*
     * Returns the Q-Value stored for a particular state-action pair.
     * */
    double Q(int state, int action)
    {
        return table[state][action];
    }

    /*----------------------------------------------------------------------------*/
    /*                              UTIL FUNCTIONS                                */
    /*----------------------------------------------------------------------------*/

    /*
     * Checks the 'reward_input' member variable and returns the corresponding reward signal.
     * */
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
            std::cout << "[Agent::get_reward_signal] Not yet implemented: " << reward_input << std::endl;
            reward_signal = stats->cTime;
        }
        else
        {
            std::cout << "[Agent::get_reward_signal] Invalid reward signal specified in env: " << reward_input << std::endl;
        }

        return reward_signal;
    }

    /*
     * Returns the sum of values (double) in an array.
     * */
    static double sum(const double* array, int length)
    {
        double sum = 0.0f;

        for (int i = 0; i < length; i++)
            sum += array[i];

        return sum;
    }

    void alpha_decay(int episode)
    {
        alpha = fmax(alpha * (episode * alpha_decay_factor), alpha_min);
    }

    void epsilon_decay(int episode)
    {
        epsilon = fmax(epsilon * (episode * epsilon_decay_factor), epsilon_min);
    }
};
