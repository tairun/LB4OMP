#include <string>
#include <unordered_map>

#include "rl_agent.hpp"
#include "q_learner_old.hpp"
#include "../../thirdparty/json.hpp"

#define STATES 12
#define ACTIONS 12
#define TRIAL_EPISODES 144

// public
QLearnerOld::QLearnerOld() {

}

void QLearnerOld::startLearning(int loop_id, const json *agent_options) {
    agent_data.insert(std::make_pair(loop_id, RLinfo()));

    agent_data.at(loop_id).state = 0;
    agent_data.at(loop_id).action = 0;
    agent_data.at(loop_id).trialstate = 0;
    agent_data.at(loop_id).lowTime = -99.0; // TODO: Why are the values initialized negative?
    agent_data.at(loop_id).highTime = -999.0; // TODO: Why are the values initialized negative?
    agent_data.at(loop_id).bestqvalue = 0;
    agent_data.at(loop_id).timestep_counter = 0;

    agent_data.at(loop_id).alpha = agent_options->alpha;
    agent_data.at(loop_id).gamma = agent_options->gamma;

    int s, a;

    for (s = 0; s < STATES; s++)
        for (a = 0; a < ACTIONS; a++) {
            agent_data.at(loop_id).count[a] = 0;
            agent_data.at(loop_id).qvalue[s][a] = -299.0; // Don't know about this one.
        }

    return;
}

int QLearnerOld::doLearning() {}

// private
int QLearnerOld::getState(int timestep, std::string loop_id) {
    if (timestep < TRIAL_EPISODES) { // Have we finished exploring and are ready
        // to start exploiting?
        if ((timestep % ACTIONS) == 0) {
            if ((timestep % TRIAL_EPISODES) == 0) {
                agent_data.at(loop_id).trialstate = 0;
            } else {
                agent_data.at(loop_id).trialstate++;
            }
        }
        agent_data.at(loop_id).state = agent_data.at(loop_id).trialstate;
    }
    return agent_data.at(loop_id).state;
}

int QLearnerOld::selectAction(int timestep, int state, std::string loop_id) {
    int i, action, action_max;

    if (timestep < TRIAL_EPISODES) {
        action = timestep % ACTIONS;
    } else {
        action_max = 0;
        for (i = 0; i < ACTIONS; i++)
            if (agent_data.at(loop_id).qvalue[state][i] >
                agent_data.at(loop_id).qvalue[state][action_max])
                action_max = i;
        action = action_max;
    }
    agent_data.at(loop_id).count[action] += 1;
    return action;
}

int QLearnerOld::computeMethod(int timestep, std::string loop_id) {
    int state = 0, method = 0;

    state = getState(timestep, loop_id);
    method = selectAction(timestep, state, loop_id);
    return method;
}

double QLearnerOld::getMax_Q(int state, std::string loop_id) {
    double maxQ;
    int i, j;
    /* Q-Learning */
    /* Select best overall action (disregarding current state) */
    maxQ = agent_data.at(loop_id).qvalue[0][0];
    for (i = 1; i < STATES; i++)
        for (j = 0; j < ACTIONS; j++)
            if (agent_data.at(loop_id).qvalue[i][j] > maxQ) {
                maxQ = agent_data.at(loop_id).qvalue[i][j];
                agent_data.at(loop_id).state = j;
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

void QLearnerOld::getReward(double exectime, int action, std::string loop_id) {

    double qval, qbest;
    int reward, state;

    // Good case
    if ((exectime) < agent_data.at(loop_id).lowTime) {
        agent_data.at(loop_id).lowTime = exectime;
        reward = 2;
    }
    // Neutral case
    if ((exectime > agent_data.at(loop_id).lowTime) &&
        (exectime < agent_data.at(loop_id).highTime)) {
        agent_data.at(loop_id).lowTime = exectime;
        reward = 0;
    }
    // Bad case
    if (exectime > agent_data.at(loop_id).highTime) {
        agent_data.at(loop_id).highTime = exectime;
        reward = -2;
    }

    state = agent_data.at(loop_id).state;
    qval = agent_data.at(loop_id).qvalue[state][action];
    qbest = getMax_Q(state, loop_id);
    agent_data.at(loop_id).qvalue[state][action] =
            qval + agent_data.at(loop_id).alpha *
                   (reward + (agent_data.at(loop_id).gamma * qbest) -
                    qval); // Do the actual learning

    return;
}

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
