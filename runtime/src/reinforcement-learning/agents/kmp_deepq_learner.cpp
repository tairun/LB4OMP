#include "kmp_agent.h"
#include "kmp_deepq_learner.h"
//#include "../../thirdparty/MiniDNN/include/MiniDNN.h"


// public
DeepQLearner::DeepQLearner(int num_states, int num_actions)
    : Agent(num_states, num_actions, "DQN-Learner") {
  // TODO: Implementation
}

// private
void DeepQLearner::update(int next_state, int next_action,
                          double reward_value) {
  // TODO@kurluc00: Implement
}
