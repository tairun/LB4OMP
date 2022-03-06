#include <string>
#include <iostream>
#include "kmp_r_learner.h"


// public
RLearner::RLearner(int states, int actions) :
          RLAgent(states, actions, "R Learner")
{

}

int RLearner::step(int timestep, LoopData* stats)
{
    return 0;
}

// private
