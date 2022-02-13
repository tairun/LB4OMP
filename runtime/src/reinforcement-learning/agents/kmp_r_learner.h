#pragma once

#include <string>
#include "kmp_rl_agent_new.h"


class RLearner : public RLAgentNew {
public:
    explicit RLearner(int states, int actions);

    ~RLearner() = default;

    int doLearning(int timestep, LoopData* stats) override;

private:

};
