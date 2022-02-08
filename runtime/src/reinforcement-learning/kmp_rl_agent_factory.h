#pragma once

#include <string>
#include <unordered_map>

#include "agents/kmp_rl_agent.h"
#include "kmp_agent_type.h"

class RLAgentFactory {
public:
    /* Destructor */
    ~RLAgentFactory() = default;

    static int rlAgentSearch(const std::string &loop_id, int agent_type, double reward_signal, int portfolio_size);

    /* Creates and return a pointer to a learning agent with the specified type
     * and options. */
    static RLAgent* create_agent(const std::string &loop_id, int type, int states, int actions, int offset);

private:
    //static std::unordered_map<std::string, int> timesteps; // We need to keep track of the elapsed timesteps. TODO: Is this already done?
    static std::unordered_map<std::string, int>& GetTimesteps();
    //static std::unordered_map<std::string, RLAgent *> agents; // Keep a reference to all the agents for every loop.
    static std::unordered_map<std::string, RLAgent*>& GetAgents();

    /* Disallow creating an instance of this object */
    RLAgentFactory() = default;
};
