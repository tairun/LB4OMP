#include <string>
#include <iostream>

#include "kmp_rl_agent_old.h"
#include "kmp_q_learner_old.h"
#include "kmp_r_learner.h"


// public
RLearner::RLearner(int states, int actions) : RLAgentNew(states, actions)
{

}

int RLearner::doLearning(int timestep, LoopData* stats)
{
    return 0;
}

// private
