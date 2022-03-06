#include "kmp_rl_agent.h"

class DeepQLearner : public RLAgent {
public:
    explicit DeepQLearner(int numStates, int numActions);

    ~DeepQLearner() = default;

    int step(int timestep, LoopData *stats) override;

private:
    int state;
    int *count;
    double low, high;
    double** qTableA;
    double** qTableB;
    double** qTableSum;

    double alpha;
    double gamma;
    double epsilon;

    /* The Policy chooses an action according to the learned experience of the agent. */
    int policy();

    /* The reward function is designed to convert the actions into a number representation. */
    double reward(double rewardSignal);

    /* Updates the internal values of the agent. */
    void updateQTable(int nextState, double rewardValue);

    /* Returns the index of the largest value in an array. */
    int argMax(double** table, int nextState);
};
