#include "kmp_agent.h"

class DoubleQLearner : public Agent
{
public:
    explicit DoubleQLearner(int num_states, int num_actions);

    ~DoubleQLearner() = default;

private:
    double** q_table_a{nullptr};
    double** q_table_b{nullptr};
    double** q_table_sum{nullptr};

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
