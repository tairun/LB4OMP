#include "kmp_rl_agent.h"

class DoubleQLearner : public RLAgent
{
public:
    explicit DoubleQLearner(int num_states, int num_actions);

    ~DoubleQLearner() = default;

private:
    double** q_table_a;
    double** q_table_b;
    double** q_table_sum;

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
