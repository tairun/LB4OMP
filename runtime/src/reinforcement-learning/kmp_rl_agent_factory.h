#pragma once

#include <string>
#include <unordered_map>

#include "agents/kmp_rl_agent.h"


class RLAgentFactory {
public:
    /* Destructor */
    ~RLAgentFactory() = default;

    /*
    * Creates and returns a pointer to a learning agent with the specified type and options.
    * */
    static RLAgent* create_agent(int type, LoopData* stats, int states, int actions, int offset);

    /*
     * Main method for Reinforcement Learning AUTO method in LB4OMP.
     * */
    static int rlAgentSearch(const std::string &loop_id, int agent_type, LoopData* stats, int portfolio_size);

    /*
     * Stores timestep data for logging.
     * */
    static void add_csv_data()
    {

    }

    /*
     * Writes timestep data to file.
     * */
    static void write_csv_data()
    {

    }


private:
    //static std::unordered_map<std::string, int> timesteps; // We need to keep track of the elapsed timesteps. TODO: Is this already done?
    static std::unordered_map<std::string, int>& get_timesteps();
    //static std::unordered_map<std::string, RLAgent *> agents; // Keep a reference to all the agents for every loop.
    static std::unordered_map<std::string, RLAgent*>& get_agents();

    /* Prevent instancing of this object */
    RLAgentFactory() = default;
};
