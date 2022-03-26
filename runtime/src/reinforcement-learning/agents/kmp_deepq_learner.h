#pragma once

#include "kmp_rl_agent.h"
//#include "../../thirdparty/MiniDNN/include/MiniDNN.h"

class DeepQLearner : public RLAgent {
public:
    explicit DeepQLearner(int num_states, int num_actions);

    ~DeepQLearner() = default;

private:
    // Import DQN network

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
