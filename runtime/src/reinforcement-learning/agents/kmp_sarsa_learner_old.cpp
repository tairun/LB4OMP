#include <string>
#include <unordered_map>
#include <iostream>

#include "kmp_rl_info.h"
#include "kmp_rl_agent_old.h"
#include "kmp_sarsa_learner_old.h"

// public
SARSALearnerOld::SARSALearnerOld(int states, int actions) : RLAgentOld(states, actions)
{
    agent_data = new RLInfo(states, actions);
}

int SARSALearnerOld::doLearning(int timestep, LoopData* stats)
{
    double reward_signal;

    if (reward_input == "looptime")
    {
        reward_signal = stats->cTime;
    } else if (reward_input == "loadimbalance")
    {
        reward_signal = stats->cLB;
    } else if (reward_input == "robustness")
    {
        std::cout << "Reinforcement Learning: Not yet implemented" << std::endl;
        reward_signal = stats->cTime;
    } else
    {
        std::cout << "Reinforcement Learning: Invalid reward signal specified in env: " << reward_input << std::endl;
    }

    int method = computeMethod(timestep);
    getReward(reward_signal, method);

    return method;
}

// private
int SARSALearnerOld::getState(int timestep)
{
    if (timestep < (states * actions)) {
        if ((timestep % actions) == 0) {
            if ((timestep % (states * actions)) == 0) {
                agent_data->trialstate = 0;
            } else {
                agent_data->trialstate++;
            }
        }
        agent_data->state = agent_data->trialstate;
    }
    return agent_data->state;
}

int SARSALearnerOld::selectAction(int timestep, int state)
{
    int i, action, action_max;

    if (timestep < (states * actions)) {
        action = timestep % actions;
    } else {
        action_max = 0;
        for (i = 0; i < actions; i++)
            if (agent_data->qvalue[state][i] >
                agent_data->qvalue[state][action_max])
                action_max = i;
        action = action_max;
    }
    agent_data->count[action] += 1;
    return action;
}

int SARSALearnerOld::computeMethod(int timestep)
{
    int state = 0, method = 0;

    state = getState(timestep);
    method = selectAction(timestep, state);
    return method;
}

double SARSALearnerOld::getMax_Q(int state)
{
    double maxQ;
    int j;
    /* SARSA*/
    /* Select best action based on qvalue of current state */
    maxQ = agent_data->qvalue[state][0];
    for (j = 1; j < actions; j++)
    if (agent_data->qvalue[state][j] > maxQ) {
        maxQ = agent_data->qvalue[state][j];
        agent_data->state = j;
    }

return maxQ;
}

void SARSALearnerOld::getReward(double exectime, int action)
{

    double qval, qbest;
    int reward, state;

    // Good case
    if ((exectime) < agent_data->low) {
        agent_data->low = exectime;
        reward = 2;
    }
    // Neutral case
    if ((exectime > agent_data->low) &&
        (exectime < agent_data->high)) {
        agent_data->low = exectime;
        reward = 0;
    }
    // Bad case
    if (exectime > agent_data->high) {
        agent_data->high = exectime;
        reward = -2;
    }

    state = agent_data->state;
    qval = agent_data->qvalue[state][action];
    qbest = getMax_Q(state);
    agent_data->qvalue[state][action] =
            qval + agent_data->alpha *
                   (reward + (agent_data->gamma * qbest) -
                    qval); // Do the actual learning

return;
}

/*
void SARSALearnerOld::printQValues(std::string loop_id)
{
    int s, a;

    printf("<-start-qvalues->:%s\n", loop_id.c_str());
    for (s = 0; s < STATES; s++) {
        for (a = 0; a < ACTIONS; a++) {
            printf("%6.2lf,", agent_data.at(loop_id).qvalue[s][a]);
        }
        printf("\n");
    }
}

void SARSALearnerOld::printDlsFreq(std::string loop_id)
{
    int aidx;
    printf("<-start-dls-freq->:%s\n", loop_id.c_str());
    for (aidx = 0; aidx < ACTIONS; aidx++)
        printf("%3.0d,", agent_data.at(loop_id).count[aidx]);
    printf("\n");
    return;
}
*/
