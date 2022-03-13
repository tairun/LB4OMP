#pragma once

#include <string>
#include "kmp_rl_agent_new.h"


class RLearner : public RLAgent {
public:
    explicit RLearner(int num_states, int num_actions);

    ~RLearner() = default;

private:
    double** q_table;

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
