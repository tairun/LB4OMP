#pragma once

#include <string>

#include "../../thirdparty/json.hpp"

class RLAgent {
public:
    RLAgent();

    virtual ~RLAgent();

    /* Setup the agent with the necessary information. */
    virtual void startLearning(std::string loop_id, nlohmann::json *agent_options) = 0;

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int doLearning(std::string loop_id, int timestep, double reward_signal) = 0;

private:
};
