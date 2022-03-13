#include "kmp_rl_agent.h"


class QVLearner : public RLAgent {
public:
    explicit QVLearner(int num_states, int num_actions);

    ~QVLearner() = default;

private:
    double** q_table;
    double* v_table;

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;
};
