#include <string>

#include "kmp_rl_agent_new.h"
#include "kmp_rl_info.h"

class RLearner : public RLAgentNew {
public:
    explicit RLearner(int states, int actions);

    ~RLearner() = default;

    int doLearning(int timestep, double reward_signal) override;

private:

};
