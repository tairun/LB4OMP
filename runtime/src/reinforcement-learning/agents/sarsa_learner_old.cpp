#include <string>
#include <unordered_map>

#include "rl_agent.hpp"
#include "sarsa_learner_old.hpp"

#define STATES 12
#define ACTIONS 12
#define TOTAL_CELLS 144

class SarsaLearnerOld : public rl_agent {
public:
    SarsaLearnerOld(const std::string &name, const std::string &type,
                  const std::string &id, const std::string &config);

    virtual ~q_learner_old();

    virtual void do_learning();

private:
    std::string name_;
    std::string type_;
    std::string id_;
    std::string config_;
    std::unordered_map <std::string, RLinfo>
            agent_data; // Saving the state of the agent between timesteps
    // double ALPHA = 0.50; // Learning rate
    // double GAMMA = 0.15; // Discount factor
    int TRIAL_EPISODES; // TRIAL_EPISODES denotes how many times the RL agent
    // should just learn and not select something due to its
    // policy
    // int RLMETHOD = 0; // RLMETHOD denotes which learning strategy should be
    // employed by the getMax_Q function: 0=Q-LEARN, 1=SARSA

    /*
     * Initializes the RLinfo struct for each loop
     * */
    void startLearn(std::string loop_id) {
        agent_data.insert(std::make_pair(loop_id, RLinfo()));
        agent_data.at(loop_id).state = 0;
        agent_data.at(loop_id).action = 0;
        agent_data.at(loop_id).trialstate = 0;
        agent_data.at(loop_id).lowTime =
                -99.0; // TODO: Why are the values initialized negative?
        agent_data.at(loop_id).highTime =
                -999.0; // TODO: Why are the values initialized negative?
        agent_data.at(loop_id).bestqvalue = 0;
        agent_data.at(loop_id).timestep_counter = 0;

        if (std::getenv("KMP_RL_ALPHA") != NULL) {
            agent_data.at(loop_id).alpha = std::stod(std::getenv("KMP_RL_ALPHA"));
        } else {
            agent_data.at(loop_id).alpha = 0.6;
        }

        if (std::getenv("KMP_RL_GAMMA") != NULL) {
            agent_data.at(loop_id).gamma = std::stod(std::getenv("KMP_RL_GAMMA"));
        } else {
            agent_data.at(loop_id).gamma = 0.6;
        }

        if (std::getenv("KMP_RL_LMETHOD") != NULL) {
            agent_data.at(loop_id).method = std::atoi(std::getenv("KMP_RL_LMETHOD"));
        } else {
            agent_data.at(loop_id).method = 1;
        }

        int s, a;

        for (s = 0; s < STATES; s++)
            for (a = 0; a < ACTIONS; a++) {
                agent_data.at(loop_id).count[a] = 0;
                agent_data.at(loop_id).qvalue[s][a] =
                        -299.0; // Don't know about this one.
            }

        return;
    }

    /*
        Get the state (which method of scheduling) for a specific loop.
        Do special stuff when still in TRIAL phase (exploration?)
        try:int: timestep?
        choice:int: loop identifier? // We don't need this parameter here, because
       loop ID is "global"
    */
    int getState(int timestep, std::string loop_id) {
        if (timestep < TRIAL_EPISODES) { // Have we finished exploring and are ready
            // to start exploiting?
            if ((timestep % ACTIONS) == 0) {
                if ((timestep % TOTAL_CELLS) == 0) {
#ifdef RLDEBUG
                    printf("Reset trialstate!\n");
#endif
                    agent_data.at(loop_id).trialstate = 0;
                } else {
#ifdef RLDEBUG
                    printf("Forcing new trialstate!\n");
#endif
                    agent_data.at(loop_id).trialstate++;
                }
            }
            agent_data.at(loop_id).state = agent_data.at(loop_id).trialstate;
        }
        return agent_data.at(loop_id).state;
    }

    /*
        Implements e-greedy policy?`
        time:int: timestep?
        s:int: current state
        choice:int: current loop id // We don't need this parameter here, because
       loop ID is "global"
    */
    int selectAction(int timestep, int state, std::string loop_id) {
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

    /*
     * Gets the new DLS method via the selectAction function
     * */
    int computeMethod(int timestep, std::string loop_id) {
        int state = 0, method = 0;

        state = getState(timestep, loop_id);
        method = selectAction(timestep, state, loop_id);
        return method;
    }

    double getMax_Q(int state, std::string loop_id) {
        double maxQ;
        int i, j;
        /* Q-Learning */
        /* Select best overall action (disregarding current state) */
        if (agent_data.at(autoLoopName).method == 0) {
            maxQ = agent_data.at(loop_id).qvalue[0][0];
            for (i = 1; i < STATES; i++)
                for (j = 0; j < ACTIONS; j++)
                    if (agent_data.at(loop_id).qvalue[i][j] > maxQ) {
                        maxQ = agent_data.at(loop_id).qvalue[i][j];
                        agent_data.at(loop_id).state = j;
                    }
            /* SARSA*/
            /* Select best action based on qvalue of current state */
        } else {
            maxQ = agent_data.at(loop_id).qvalue[state][0];
            for (j = 1; j < ACTIONS; j++)
                if (agent_data.at(loop_id).qvalue[state][j] > maxQ) {
                    maxQ = agent_data.at(loop_id).qvalue[state][j];
                    agent_data.at(loop_id).state = j;
                }
        }
        return maxQ;
    }

    /*
        Updates the qvalue according to the Bellman equation depending on the loop
       id, selected action and execution time *exectime:double: Execution time for
       the loop in this timestep *action:int: seleceted action in previous step
        *choice:int: current loop id
    */
    void getReward(double exectime, int action, std::string loop_id) {

        double qval, qbest;
        int reward, state;

#ifdef RLDEBUG
        printf("getReward(): Exectime is: %lf (LowTime: %lf, Hightime: %lf)\n",
           exectime, agent_data.at(loop_id).lowTime,
           agent_data.at(loop_id).highTime);
#endif
        // Good case
        if ((exectime) < agent_data.at(loop_id).lowTime) {
#ifdef RLDEBUG
            printf("getReward(): Good case\n");
#endif
            agent_data.at(loop_id).lowTime = exectime;
            reward = 2;
        }
        // Neutral case
        if ((exectime > agent_data.at(loop_id).lowTime) &&
            (exectime < agent_data.at(loop_id).highTime)) {
#ifdef RLDEBUG
            printf("getReward(): Neutral case\n");
#endif
            agent_data.at(loop_id).lowTime = exectime;
            reward = 0;
        }
        if (exectime > agent_data.at(loop_id).highTime) { // Bad case
#ifdef RLDEBUG
            printf("getReward(): Bad case\n");
#endif
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

    void printQValues(std::string loop_id) {
        int s, a;

        printf("<-start-qvalues->:%s\n", loop_id.c_str());
        for (s = 0; s < STATES; s++) {
            for (a = 0; a < ACTIONS; a++) {
                printf("%6.2lf,", agent_data.at(loop_id).qvalue[s][a]);
            }
            printf("\n");
        }
    }

    void printDlsFreq(std::string loop_id) {
        int aidx;
        printf("<-start-dls-freq->:%s\n", loop_id.c_str());
        for (aidx = 0; aidx < ACTIONS; aidx++)
            printf("%3.0d,", agent_data.at(loop_id).count[aidx]);
        printf("\n");
        return;
    }
};
