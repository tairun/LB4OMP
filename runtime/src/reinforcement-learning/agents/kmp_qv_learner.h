#include "kmp_agent.h"


class QVLearner : public Agent {
public:
    explicit QVLearner(int num_states, int num_actions);

    ~QVLearner() = default;

private:
    double** q_table{nullptr};
    double* v_table{nullptr};

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;

    /* Returns the V-Value stored for a particular state. */
    double V(int state);
};
