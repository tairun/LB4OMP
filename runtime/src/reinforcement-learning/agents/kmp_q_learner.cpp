// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <random>

#include "reinforcement-learning/utils/utils.h"
#include "reinforcement-learning/agents/kmp_agent.h"
#include "reinforcement-learning/agents/kmp_q_learner.h"


// public
QLearner::QLearner(int num_states, int num_actions) :
          Agent(num_states, num_actions, "Q-Learner")
{
    // Initialize first dimension of table
    std::cout << "[ALearner::QLearner] Using init ..." << std::endl;
    pInit->init(q_table, state_space, action_space);
    std::cout << "[ALearner::QLearner] Done using init." << std::endl;
    set_table(q_table);
}

// private
void QLearner::update(int next_state, int next_action, int actions,double reward_value)
{
    int best_action = argmax(q_table, next_state, actions);
    q_table[current_state][current_action] += alpha * (reward_value + gamma * Q(next_state, best_action) - Q(current_state, current_action));
}
