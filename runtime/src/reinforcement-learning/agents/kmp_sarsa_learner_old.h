#include <string>

#include "kmp_rl_agent_old.h"
#include "kmp_rl_info.h"

class SARSALearnerOld : public RLAgentOld {
public:
    explicit SARSALearnerOld(const std::string& loop_id, int states, int actions);

    ~SARSALearnerOld() = default;

    int doLearning(const std::string& loop_id, int timestep, double reward_signal) override;

private:
    /*
     * Get the state for a specific loop.
     */
    int getState(int timestep, const std::string& loop_id);

    /*
     * Implements greedy policy`
     * time:int: timestep?
     * s:int: current state
     * choice:int: current loop id // We don't need this parameter here, because
     * loop ID is "global"
     */
    int selectAction(int timestep, int state, const std::string& loop_id);

    /*
     * Gets the new DLS method via the selectAction function
     */
    int computeMethod(int timestep, const std::string& loop_id);

    double getMax_Q(int state, const std::string& loop_id);

    /*
     * Updates the qvalue according to the Bellman equation depending on the loop
     * the loop in this timestep *action:int: seleceted action in previous step
     * choice:int: current loop id
     */
    void getReward(double exectime, int action, const std::string& loop_id);
};
