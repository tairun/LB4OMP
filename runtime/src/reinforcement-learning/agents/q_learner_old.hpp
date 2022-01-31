#include <string>

#include "rl_agent.hpp"
#include "../../thirdparty/json.hpp"

class QLearnerOld : public RLAgent {
public:
    QLearnerOld(json agent_options);

    virtual ~QLearnerOld();

    /*
     * Initializes the RLInfo struct for each loop
     */
    void startLearning(std::string loop_id, json *agent_options);

    virtual int doLearning();

private:
    std::unordered_map<std::string, RLinfo> agent_data; // Saving the state of the agent between timesteps

    /*
     * Get the state for a specific loop.
     */
    int getState(int timestep, std::string loop_id);

    /*
     * Implements greedy policy`
     * time:int: timestep?
     * s:int: current state
     * choice:int: current loop id // We don't need this parameter here, because
     * loop ID is "global"
     */
    int selectAction(int timestep, int state, std::string loop_id);

    /*
     * Gets the new DLS method via the selectAction function
     */
    int computeMethod(int timestep, std::string loop_id);

    double getMax_Q(int state, std::string loop_id);

    void getReward(double exectime, int action, std::string loop_id);

    /*
     * Gets the new DLS method via the selectAction function
     */
    int computeMethod(int timestep, std::string loop_id);

    double getMax_Q(int state, std::string loop_id);

    /*
     * Updates the qvalue according to the Bellman equation depending on the loop
     * the loop in this timestep *action:int: seleceted action in previous step
     * choice:int: current loop id
     */
    void getReward(double exectime, int action, std::string loop_id)

};

struct RLInfo {
    int state, action, trialstate;
    double lowTime, highTime;
    int count[ACTIONS];
    int bestqvalue;
    double qvalue[STATES][ACTIONS];
    int timestep_counter;
    double alpha;
    double gamma;
};