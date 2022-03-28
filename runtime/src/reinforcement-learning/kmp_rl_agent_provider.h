// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <string>
#include <unordered_map>

#include "agents/kmp_rl_agent.h"


class RLAgentProvider {
public:
    RLAgentProvider(const RLAgentProvider&) = delete;   // Disable copy constructor

    static RLAgentProvider& Get();
    static std::unordered_map<std::string, int>& get_timesteps();
    static std::unordered_map<std::string, RLAgent*>& get_agents();

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
    static void add_csv_data();

    /*
     * Writes timestep data to file.
     * */
    static void write_csv_data();

private:
    RLAgentProvider() = default;    // Make this class a singleton effectively
    std::unordered_map<std::string, int> timesteps;   // Save timestep progress
    std::unordered_map<std::string, RLAgent*> agents; // Save agent references across timesteps
};
