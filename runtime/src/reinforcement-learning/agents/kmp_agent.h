// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//



#include <algorithm>
#include <ctime>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <utility>

#include "defaults.h"
#include "../kmp_loopdata.h"
#include "../utils/utils.h"
#include "../rewards/kmp_reward_type.h"
#include "../initializers/kmp_init_type.h"
#include "../initializers/kmp_base_init.h"
#include "../policies/kmp_policy_type.h"
#include "../policies/kmp_base_policy.h"

#pragma once

#define RL_DEBUG 1     // Added by Reinforcement Learning Extension to minimize stdout clutter

class Agent {
public:
    Agent(int num_states, int num_actions, std::string agent_name) : state_space(num_states),
                                                                     action_space(num_actions),
                                                                     name(std::move(agent_name))
    {
        read_env_double("KMP_RL_ALPHA", alpha);     // Read learning rate from env
        read_env_double("KMP_RL_GAMMA", gamma);     // Read discount factor from env
        read_env_double("KMP_RL_EPSILON", epsilon); // Read exploration rate from env

        alpha_init = alpha;
        epsilon_init = epsilon;

        read_env_enum("KMP_RL_REWARD", reward_type);
        read_env_enum("KMP_RL_INIT", init_type);
        read_env_enum("KMP_RL_POLICY", policy_type);

        read_env_string("KMP_RL_REWARD_NUM", reward_string);

        split_reward_nums();

        read_env_double("KMP_RL_ALPHA_DECAY", alpha_decay_factor);
        read_env_double("KMP_RL_EPS_DECAY", epsilon_decay_factor);

#if (RL_DEBUG > 0)
        std::cout << "[Agent::Agent] Configuring agent as: " << name << std::endl;
        std::cout << "[Agent::Agent] Additional params: Initializer-->" << init_type << ", Reward-->" << reward_type << ", Policy-->" << policy_type << std::endl;
#endif
    }

    /*
     * Takes reward and performs the learning process. Returns the prediction for the next action from the agent.
     * */
    virtual int step(int episode, int timestep, LoopData* stats)
    {
#if (RL_DEBUG > 1)
        std::cout << "[Agent::step] Starting learning ..." << std::endl;
#endif
        int next_action, next_state;
        double reward_value = reward(stats);                              // Convert the reward signal into the actual reward value
        next_action = pPolicy->policy(episode, timestep, this);     // Predict the next action according to the policy and Q-Values
        next_state = next_action;                                         // In our scenario the next action and desired state is the same
#if (RL_DEBUG > 1)
        std::cout << "[Agent::update] Updating agent data ..." << std::endl;
#endif
        update(next_state, next_action, reward_value);                    // Update the Q-Values based on the learning algorithm

        current_state = next_state;                    // Update the state in the class
        current_action = next_action;                  // Update the action in the class
        current_reward = reward_value;                 // Update the reward in the class (for statistics only)

        // Decay
        if (policy_type == PolicyType::EXPLORE_FIRST)
        {
            if (timestep >= (state_space * action_space))
            // Delay the decay if we are using EXPLORE_FIRST action selection policy
            {
                // We offset the timesteps by the amount of exploration done, to correctly calculate the decay
                if (alpha_decay_factor > 0)
                    // Only decay if the decay factor is greater than zero
                    decay(timestep-(state_space * action_space), alpha, alpha_init, alpha_min, alpha_decay_factor);
                if (epsilon_decay_factor > 0)
                    // Only decay if the decay factor is greater than zero
                    decay(timestep-(state_space * action_space), epsilon, epsilon_init, epsilon_min, epsilon_decay_factor);
            }

        } else {
            if (alpha_decay_factor > 0)
                // Only decay if the decay factor is greater than zero
                decay(timestep, alpha, alpha_init, alpha_min, alpha_decay_factor);
            if (epsilon_decay_factor > 0)
                // Only decay if the decay factor is greater than zero
                decay(timestep, epsilon, epsilon_init, epsilon_min, epsilon_decay_factor);
        }

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

    std::string get_name() {
        return name;
    }

    void set_name(std::string new_name) {
        name = std::move(new_name);
    }

    std::string get_rewards_string()
    {
        return reward_string;
    }

    RewardType get_reward_type() {
        return reward_type;
    }

    InitType get_init_type() {
        return init_type;
    }

    PolicyType get_policy_type() {
        return policy_type;
    }

    double get_alpha() const {
        return alpha;
    }

    double get_alpha_init() const {
        return alpha_init;
    }

    double get_alpha_min() const {
        return alpha_min;
    }

    double get_alpha_decay() const {
        return alpha_decay_factor;
    }

    double get_gamma() const {
        return gamma;
    }

    double get_epsilon_init() const {
        return epsilon_init;
    }

    double get_epsilon_min() const {
        return epsilon_min;
    }

    double get_epsilon_decay() const {
        return epsilon_decay_factor;
    }

    double get_epsilon() const {
        return epsilon;
    }

    int get_state_space() const {
        return state_space;
    }

    int get_action_space() const {
        return action_space;
    }

    InitType get_init_input() const {
        return init_type;
    }

    PolicyType get_policy_input() const {
        return policy_type;
    }

    double** get_table() const {
        return table;
    }

    int get_current_state() const {
        return current_state;
    }

    double get_current_reward() const {
        return current_reward;
    }

    double get_low() const {
        return low;
    }

    double get_high() const {
        return high;
    }

    // Setters
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
    double   seed{420.69};     // Controls the seed for the number generators
    double** table{nullptr}; // Pointer to table to lookup the best next action

protected:
    BaseInit*   pInit{nullptr};
    BasePolicy* pPolicy{nullptr};

    double* reward_num{nullptr};

    int state_space;       // Amount of states in the environment. Exported to agent.ini
    int action_space;      // Amount of action available to the agent. Exported to agent.ini
    int current_state{0};  // We always start with static scheduling method as initial state (it's the first method from the portfolio)
    int current_action{0}; // Set action also to selecting the static scheduling method

    double current_reward{0};                  // For statistics only

    double alpha{defaults::ALPHA};             // Learning rate (changes over execution)
    double alpha_init{defaults::ALPHA};        // Learning rate. Exported to agent.ini
    double alpha_min{defaults::ALPHA_MIN};     // Learning rate. Exported to agent.ini
    double alpha_decay_factor{defaults::ALPHA_DECAY_FACTOR};  // Exported to agent.ini

    double gamma{defaults::GAMMA};             // Discount factor

    double epsilon{defaults::EPSILON};         // Exploration rate (changes over execution)
    double epsilon_init{defaults::EPSILON};    // Exploration rate. Exported to agent.ini
    double epsilon_min{defaults::EPSILON_MIN}; // Exploration rate. Exported to agent.ini
    double epsilon_decay_factor{defaults::EPSILON_DECAY_FACTOR}; // Exported to agent.ini

    double low{999.00f}, high{0.00f};          // Initial value for reward allocation. This needs to be defined in the context of your RL problem. In our case this represents the millis for the loop iteration

    std::string name;                               // Name of the agent (human-readable). Exported to agent.ini
    std::string reward_string{defaults::REWARD_STRING};
    RewardType reward_type{defaults::REWARD_TYPE};  // Default: looptime.      Options are: looptime, loadimbalance, robustness. Exported to agent.ini
    InitType init_type{defaults::INIT_TYPE};        // Default: zero.          Options are: zero, random, optimistic. Exported to agent.ini
    PolicyType policy_type{defaults::POLICY_TYPE};  // Default: explore_first. Options are: explore_first, epsilon_greedy, softmax. Exported to agent.ini

    /*----------------------------------------------------------------------------*/
    /*                            MEMBER FUNCTIONS                                */
    /*----------------------------------------------------------------------------*/

    /* The policy chooses an action according to the learned experience of the agent. */
    /* Implements the Epsilon-Greedy action selection. */
    virtual int policy(int episode, int timestep, double** ref_table)
    {
#if (RL_DEBUG > 1)
        std::cout << "[Agent::policy] Applying policy ..." << std::endl;
#endif
        std::default_random_engine re(seed);
        std::uniform_real_distribution<double> uniform(0, 1);

        // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
        if (uniform(re) < epsilon)
        // Explore (random action)
        {
#if (RL_DEBUG > 1)
            std::cout << "[Agent::policy] Exploring" << std::endl;
#endif
            int next_action = sample_action(); // Chooses action (which is equal to the next state)
            return next_action;
        }
        else
        // Exploit (previous knowledge)
        {
#if (RL_DEBUG > 1)
            std::cout << "[Agent::policy] Exploiting" << std::endl;
#endif
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
#if (RL_DEBUG > 1)
        std::cout << "[Agent::reward] Getting reward ..." << std::endl;
#endif
        //TODO@kurluc00: Explore negative vs. positive Rewards discussion for agents.
        double reward_signal = get_reward_signal(stats);
#if (RL_DEBUG > 0)
        std::cout << "[Agent::reward] High: " << high << ", Low: " << low << ", Reward: " << reward_signal << std::endl;
#endif
        // Good case
        if ((reward_signal) < low)
        {
#if (RL_DEBUG > 1)
            std::cout << "[Agent::reward] Good!" << std::endl;
#endif
            low = reward_signal;
            return reward_num[0]; // by default: 0.0
        }
        // Neutral case
        if ((reward_signal > low) && (reward_signal < high))
        {
#if (RL_DEBUG > 1)
            std::cout << "[Agent::reward] Neutral." << std::endl;
#endif
            return reward_num[1]; // by default: -2.0
        }
        // Bad case
        if (reward_signal > high)
        {
#if (RL_DEBUG > 1)
            std::cout << "[Agent::reward] Bad!" << std::endl;
#endif
            high = reward_signal;
            return reward_num[2]; // by default: -4.0
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
     * Checks the 'reward_type' member variable and returns the corresponding reward signal.
     * */
    double get_reward_signal(LoopData* stats)
    {
        double reward_signal = 0;

        if (reward_type == RewardType::LOOPTIME)
        {
            reward_signal = stats->cTime;
        }
        else if (reward_type == RewardType::LOADIMBALANCE)
        {
            reward_signal = stats->cLB;
        }
        else if (reward_type == RewardType::ROBUSTNESS)
        {
            std::cout << "[Agent::get_reward_signal] Not yet implemented: " << reward_type << std::endl;
            reward_signal = stats->cTime;
        }
        else
        {
            std::cout << "[Agent::get_reward_signal] Invalid reward signal specified in env: " << reward_type << std::endl;
        }

        return reward_signal;
    }

    static void decay(const int timestep, double& target, const double target_init, const double target_min, const double factor)
    {
        target = fmax(target_min, target_init * exp(-factor * timestep));
    }

    void split_reward_nums()
    {
        reward_num = new double[3];
        std::string rewards_copy = reward_string;
        size_t pos = 0;
        int index = 0;
        std::string token;

        while ((pos = rewards_copy.find(',')) != std::string::npos) {
            token = rewards_copy.substr(0, pos);
            reward_num[index] = std::stod(token);
            rewards_copy.erase(0, pos+1);
            index++;
        }

        reward_num[index] = std::stod(rewards_copy);

    }
};
