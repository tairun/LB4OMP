#include "kmp_rl_agent.h"
#include "kmp_deepq_learner.h"
#include "../../thirdparty/MiniDNN/include/MiniDNN.h"


// public
DeepQLearner::DeepQLearner(int num_states, int num_actions) :
              RLAgent(num_states, num_actions, "DQN Learner", nullptr)
{
    // TODO: Implementation
}

// private
void DeepQLearner::update(int next_state, int next_action, double reward_value)
{
    //TODO@kurluc00: Implement
}
