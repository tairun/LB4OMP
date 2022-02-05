#include <string>

#include "kmp_rl_agent.h"
#include "kmp_rl_info.h"

class SarsaLearnerOld : public RLAgent {
public:
    SarsaLearnerOld(json agent_options);

    virtual ~SarsaLearnerOld();

    virtual void do_learning();

private:
    void startLearn(std::string loop_id);
};
