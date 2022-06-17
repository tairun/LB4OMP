// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//


#include "reinforcement-learning/utils/utils.h"
#include "reinforcement-learning/agents/kmp_agent.h"
#include "reinforcement-learning/agents/kmp_q_learner.h"


// public
QLearner::QLearner(int num_states, int num_actions) :
          Agent(num_states, num_actions, "Q-Learner")
{
    pInit->init(&q_table, state_space, action_space);
    dumpArray2D(q_table, state_space, action_space);
    set_table(&q_table);
}

// private
void QLearner::update(int next_state, int next_action, int actions, double reward_value)
{
    int best_action = argmax(q_table, next_state, actions);
    std::cout << "[QLearner::update] Done using argmax. Found: " << best_action << std::endl;
    double right_term = alpha * (reward_value + gamma * Q(next_state, best_action) - Q(current_state, current_action));
    std::cout << "[QLearner::update] Right term = " << right_term << std::endl;
    q_table[current_state][current_action] += right_term;
}
