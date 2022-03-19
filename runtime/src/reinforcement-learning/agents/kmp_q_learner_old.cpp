#include <string>
#include <iostream>

#include "kmp_rl_info.h"
#include "kmp_rl_agent_old.h"
#include "kmp_q_learner_old.h"

// public
QLearnerOld::QLearnerOld(int states, int actions) :
             RLAgentOld(states, actions, "Q Learner (old version)")
{
    agent_data = new RLInfo(states, actions);
}

int QLearnerOld::step(int timestep, LoopData* stats)
{
    double reward_signal = get_reward_signal(stats);
    int method = computeMethod(timestep);
    getReward(reward_signal, method);

    return method;
}

// private
int QLearnerOld::getState(int timestep)
{
    if (timestep < (state_space * action_space)) {
        if ((timestep % action_space) == 0) {
            if ((timestep % (state_space * action_space)) == 0) {
                agent_data->trialstate = 0;
            } else {
                agent_data->trialstate++;
            }
        }
        agent_data->state = agent_data->trialstate;
    }
    return agent_data->state;
}

int QLearnerOld::selectAction(int timestep, int state)
{
    int i, action, action_max;

    if (timestep < (state_space * action_space)) {
        action = timestep % action_space;
    } else {
        action_max = 0;
        for (i = 0; i < action_space; i++)
            if (agent_data->qvalue[state][i] >
                agent_data->qvalue[state][action_max])
                action_max = i;
        action = action_max;
    }
    agent_data->count[action] += 1;
    return action;
}

int QLearnerOld::computeMethod(int timestep)
{
    int cState, nMethod;

    cState = getState(timestep);
    nMethod = selectAction(timestep, cState);
    return nMethod;
}

double QLearnerOld::getMax_Q(int state)
{
    double maxQ;
    int i, j;
    /* Q-Learning */
    /* Select best overall action (disregarding current state) */
    maxQ = agent_data->qvalue[0][0];
    for (i = 1; i < state_space; i++)
        for (j = 0; j < action_space; j++)
            if (agent_data->qvalue[i][j] > maxQ) {
                maxQ = agent_data->qvalue[i][j];
                agent_data->state = j;
            }

    /* SARSA*/
    /* Select best action based on Q-Value of current state */
    /*
    maxQ = agent_data->qvalue[state][0];
    for (j = 1; j < ACTIONS; j++)
    if (agent_data.at->qvalue[state][j] > maxQ) {
        maxQ = agent_data->qvalue[state][j];
        agent_data->state = j;
    }
    */
    return maxQ;
}

void QLearnerOld::getReward(double exectime, int action)
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
}

/****************************************************************************/

void QLearnerOld::update(int next_state, int next_action, double reward_value)
{
    // Does nothing, just need this method because of interface.
}

/*
void QLearnerOld::printQValues(std::string loop_id)
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

void QLearnerOld::printDlsFreq(std::string loop_id)
{
    int aidx;
    printf("<-start-dls-freq->:%s\n", loop_id.c_str());
    for (aidx = 0; aidx < ACTIONS; aidx++)
        printf("%3.0d,", agent_data.at(loop_id).count[aidx]);
    printf("\n");
    return;
}
*/
