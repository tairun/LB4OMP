#include <string>

#include "kmp_rl_agent_old.h"
#include "kmp_rl_info.h"


class QLearnerOld : public RLAgentOld {
public:
    explicit QLearnerOld(int states, int actions);

    ~QLearnerOld() = default;

    int step(int timestep, LoopData *stats) override;

private:
    /*
     * Get the state for a specific loop.
     */
    int getState(int timestep);

    /*
     * Implements greedy policy.
     */
    int selectAction(int timestep, int state);

    /*
     * Gets the new DLS method via the selectAction function.
     */
    int computeMethod(int timestep);

    double getMax_Q(int state);

    /*
     * Updates the qvalue according to the Bellman equation depending on the loop in this timestep.
     */
    void getReward(double exectime, int action);
};
