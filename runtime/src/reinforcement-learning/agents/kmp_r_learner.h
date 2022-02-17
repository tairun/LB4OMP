#pragma once

#include <string>
#include "kmp_rl_agent_new.h"


class RLearner : public RLAgent {
public:
    explicit RLearner(int states, int actions);

    ~RLearner() = default;

    int step(int timestep, LoopData* stats) override;

private:

};
