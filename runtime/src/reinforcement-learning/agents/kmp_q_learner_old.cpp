#include <string>
#include <unordered_map>
#include <iostream>

#include "kmp_rl_info.h"
#include "kmp_rl_agent.h"
#include "kmp_q_learner_old.h"

// public
QLearnerOld::QLearnerOld(const std::string& loop_id, int states, int actions) : RLAgent(states, actions) {
    std::cout << "We got here again 3" << std::endl;
    auto* data = new RLInfo(states, actions);
    std::cout << "We got here again 4" << std::endl;
    agent_data.insert(std::make_pair(loop_id, data));
}

int QLearnerOld::doLearning(std::string loop_id, int timestep, double reward_signal) {
    int method = computeMethod(timestep, loop_id);
    getReward(reward_signal, method, loop_id);

    return method;
}

// private
int QLearnerOld::getState(int timestep, const std::string& loop_id) {
    if (timestep < (states * actions)) {
        if ((timestep % actions) == 0) {
            if ((timestep % (states * actions)) == 0) {
                agent_data.at(loop_id)->trialstate = 0;
            } else {
                agent_data.at(loop_id)->trialstate++;
            }
        }
        agent_data.at(loop_id)->state = agent_data.at(loop_id)->trialstate;
    }
    return agent_data.at(loop_id)->state;
}

int QLearnerOld::selectAction(int timestep, int state, const std::string& loop_id) {
    int i, action, action_max;

    if (timestep < (states * actions)) {
        action = timestep % actions;
    } else {
        action_max = 0;
        for (i = 0; i < actions; i++)
            if (agent_data.at(loop_id)->qvalue[state][i] >
                agent_data.at(loop_id)->qvalue[state][action_max])
                action_max = i;
        action = action_max;
    }
    agent_data.at(loop_id)->count[action] += 1;
    return action;
}

int QLearnerOld::computeMethod(int timestep, const std::string& loop_id) {
    int state = 0, method = 0;

    state = getState(timestep, loop_id);
    method = selectAction(timestep, state, loop_id);
    return method;
}

double QLearnerOld::getMax_Q(int state, const std::string& loop_id) {
    double maxQ;
    int i, j;
    /* Q-Learning */
    /* Select best overall action (disregarding current state) */
    maxQ = agent_data.at(loop_id)->qvalue[0][0];
    for (i = 1; i < states; i++)
        for (j = 0; j < actions; j++)
            if (agent_data.at(loop_id)->qvalue[i][j] > maxQ) {
                maxQ = agent_data.at(loop_id)->qvalue[i][j];
                agent_data.at(loop_id)->state = j;
            }

    /* SARSA*/
    /* Select best action based on qvalue of current state */
    /*
    maxQ = agent_data.at(loop_id).qvalue[state][0];
    for (j = 1; j < ACTIONS; j++)
    if (agent_data.at(loop_id).qvalue[state][j] > maxQ) {
        maxQ = agent_data.at(loop_id).qvalue[state][j];
        agent_data.at(loop_id).state = j;
    }
    */
    return maxQ;
}

void QLearnerOld::getReward(double exectime, int action, const std::string& loop_id) {

    double qval, qbest;
    int reward, state;

    // Good case
    if ((exectime) < agent_data.at(loop_id)->lowTime) {
        agent_data.at(loop_id)->lowTime = exectime;
        reward = 2;
    }
    // Neutral case
    if ((exectime > agent_data.at(loop_id)->lowTime) &&
        (exectime < agent_data.at(loop_id)->highTime)) {
        agent_data.at(loop_id)->lowTime = exectime;
        reward = 0;
    }
    // Bad case
    if (exectime > agent_data.at(loop_id)->highTime) {
        agent_data.at(loop_id)->highTime = exectime;
        reward = -2;
    }

    state = agent_data.at(loop_id)->state;
    qval = agent_data.at(loop_id)->qvalue[state][action];
    qbest = getMax_Q(state, loop_id);
    agent_data.at(loop_id)->qvalue[state][action] =
            qval + agent_data.at(loop_id)->alpha *
                   (reward + (agent_data.at(loop_id)->gamma * qbest) -
                    qval); // Do the actual learning

    return;
}

/*
void QLearnerOld::printQValues(std::string loop_id) {
    int s, a;

    printf("<-start-qvalues->:%s\n", loop_id.c_str());
    for (s = 0; s < STATES; s++) {
        for (a = 0; a < ACTIONS; a++) {
            printf("%6.2lf,", agent_data.at(loop_id).qvalue[s][a]);
        }
        printf("\n");
    }
}

void QLearnerOld::printDlsFreq(std::string loop_id) {
    int aidx;
    printf("<-start-dls-freq->:%s\n", loop_id.c_str());
    for (aidx = 0; aidx < ACTIONS; aidx++)
        printf("%3.0d,", agent_data.at(loop_id).count[aidx]);
    printf("\n");
    return;
}
*/
