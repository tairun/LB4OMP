#include <string>
#include <unordered_map>
#include <iostream>

#include "kmp_rl_info.h"
#include "kmp_rl_agent_old.h"
#include "kmp_q_learner_old.h"
#include "kmp_r_learner.h"


// public
RLearner::RLearner(int states, int actions) : RLAgentNew(states, actions)
{
    agent_data = new RLInfo(states, actions);
}

int RLearner::doLearning(int timestep, double reward_signal)
{
    return 0;
}

// private
