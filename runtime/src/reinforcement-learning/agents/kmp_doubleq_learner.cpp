#include <random>
#include <algorithm>
#include "kmp_doubleq_learner.h"

// public
DoubleQLearner::DoubleQLearner(int numStates, int numActions) :
                RLAgent(numStates, numActions, "DoubleQ Learner"),
                state(0),
                low(-99.0),
                high(-999.0),
                alpha(0.6),
                gamma(0.6),
                epsilon(0.3)
{
    count = new int[states];
    qTableA = new double *[states];
    qTableB = new double *[states];
    qTableSum = new double *[states];

    for (int i = 0; i < states; i++) {
        qTableA[i] = new double[actions];
        qTableB[i] = new double[actions];
        qTableSum[i] = new double[actions];
    }

    for (int s = 0; s < states; s++)
        for (int a = 0; a < actions; a++) {
            count[a] = 0;
            qTableA[s][a] = 0.0;
            qTableB[s][a] = 0.0;
            qTableSum[s][a] = 0.0;
        }

    alpha = readEnv("KMP_RL_ALPHA");     // Read learning rate from env
    gamma = readEnv("KMP_RL_GAMMA");     // Read discount factor from env
    epsilon = readEnv("KMP_RL_EPSILON"); // Read exploration rate from env
}

int DoubleQLearner::step(int timestep, LoopData* stats)
{
    //TODO@Luc: Implement actual learning
    double rewardSignal = getRewardSignal(stats);
    double rewardValue = reward(rewardSignal);
    int nextState = policy();
    updateQTable(nextState, rewardValue);

    return nextState;
}

// private
int DoubleQLearner::policy()
{
    std::uniform_real_distribution<double> uniform1(0, 1);
    std::uniform_int_distribution<int> uniform2(0, actions);
    std::default_random_engine re;

    double epsilonGreedy = uniform1(re);

    if (epsilonGreedy < epsilon) // Switches between exploration and exploitation with the probability of epsilon (or 1-epsilon)
    {
        int nextState = uniform2(re); // Chooses action (which is equal to the next state)
        state = nextState;

        return nextState;
    }
    else
    {
        int maxQ = -9999;
        std::vector<int> actionCandidates;

        // Evaluate QTable for actions with highest QValue
        for (int i = 0; i < actions; i++)
        {
            if (qTableSum[state][i] >= maxQ)
            {
                actionCandidates.push_back(i);
            }
        }

        std::uniform_int_distribution<int> uniform3(0, (int)actionCandidates.size());
        int nextStateIndex = uniform3(re);
        int nextState = actionCandidates[nextStateIndex];
        state = nextState;

        return nextState;
    }
}

double DoubleQLearner::reward(double rewardSignal)
{
    // Good case
    if ((rewardSignal) < low)
    {
        low = rewardSignal;
        return 2.0;
    }
    // Neutral case
    if ((rewardSignal > low) && (rewardSignal < high))
    {
        return 0.0;
    }
    // Bad case
    if (rewardSignal > high)
    {
        high = rewardSignal;
        return -2.0;
    }
}

void DoubleQLearner::updateQTable(int nextState, double rewardValue)
{
    std::uniform_real_distribution<double> uniform1(0, 1);
    std::default_random_engine re;
    double updateA = uniform1(re);

    if (updateA > 0.5) // Update table A or B with probability of 0.5
    {
        int bestIndex = argMax(qTableA, nextState);
        qTableA[state][nextState] += alpha * (rewardValue + gamma * qTableB[nextState][bestIndex] - qTableA[state][nextState]);
    }
    else
    {
        int bestIndex = argMax(qTableA, nextState);
        qTableB[state][nextState] += alpha * (rewardValue + gamma * qTableA[nextState][bestIndex] - qTableB[state][nextState]);
    }

    qTableSum[state][nextState] = qTableA[state][nextState] + qTableB[state][nextState]; // Update the combined table (sum) to find best action in next step
}

int DoubleQLearner::argMax(double** table, int nextState)
{
    double bestCurrent = -9999;
    int bestIndex = 0;

    for (int i = 0; i < actions; i++)
    {
        if (table[nextState][i] > bestCurrent)
        {
            bestCurrent = table[nextState][i];
            bestIndex = i;
        }
    }
    return bestIndex;
}
