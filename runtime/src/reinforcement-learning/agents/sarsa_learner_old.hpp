#include <string>

#include "rl_agent.hpp"
#include "../../thirdparty/json.hpp"

class sarsa_learner_old : public rl_agent {
public:
    SarsaLearnerOld(json agent_options);

    virtual ~SarsaLearnerOld();

    virtual void do_learning();

private:
    void startLearn(std::string loop_id);
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