// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <string>
#include <unordered_map>
#include <fstream>

#include "agents/kmp_agent.h"


class AgentProvider {
public:
    AgentProvider(const AgentProvider&) = delete;   // Disable copy constructor

    static AgentProvider& Get();

    /*
    * Creates and returns a pointer to a learning agent with the specified type and options.
    * */
    static Agent* create_agent(int type, LoopData* stats, int states, int actions, int offset);

    /*
     * Main method for Reinforcement Learning AUTO method in LB4OMP.
     * */
    static int search(const std::string &loop_id, int agent_type, LoopData* stats, int dimension);

private:
    AgentProvider();
    ~AgentProvider();

    std::unordered_map<std::string, int> timesteps; // Save timestep progress
    std::unordered_map<std::string, Agent*> agents; // Save agent references across timesteps
    std::fstream ofs;                               // Single filestream for all the agents to write to

    static int* chunk_sizes;  // Stores the values of the chunk-sizes for the agent to try
    static std::fstream& get_filestream();
    static std::unordered_map<std::string, int>& get_timesteps();
    static std::unordered_map<std::string, Agent*>& get_agents();

    /*
     * Calculates the chunk sizes to try according to the formula:
     * chunk = iterations / (2^i * threads), where i also denotes the position
     * of the result in the array.
     * */
    static int calculate_chunks(int *array, int size, int n, int p);

    /*
     * Creates and instance of the Initializers class and returns a pointer to it.
     * */
    static BaseInit* create_initializer(Agent* agent);

    /*
     * Creates and instance of the policy class and returns a pointer to it.
     * */
    static BasePolicy* create_policy(Agent* agent);

    static BaseReward* create_reward(Agent* agent);

    static void print_agent_params(const std::string& loop_id, Agent* agent, int* chunk_sizes_array, int dim);

    /*
     * Prints the stats of the agent to evaluate performance.
     * */
    static void print_agent_stats(const std::string& loop_id, int timestep, Agent* agent);
};
