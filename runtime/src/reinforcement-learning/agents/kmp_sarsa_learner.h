#include "kmp_rl_agent.h"

class SARSALearner : public RLAgent
{
public:
    explicit SARSALearner(int num_states, int num_actions);

    ~SARSALearner() = default;

private:
    double** q_table;

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
