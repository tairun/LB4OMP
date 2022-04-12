// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include <string>
#include <unordered_map>

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
    static int search(const std::string &loop_id, int agent_type, LoopData* stats, int portfolio_size);

private:
    AgentProvider() = default;    // Make this class a singleton effectively
    std::unordered_map<std::string, int> timesteps;   // Save timestep progress
    std::unordered_map<std::string, Agent*> agents; // Save agent references across timesteps
    static std::unordered_map<std::string, int>& get_timesteps();
    static std::unordered_map<std::string, Agent*>& get_agents();

    /*
     * Creates and instance of the Initializers class and returns a pointer to it.
     * */
    static BaseInit* create_initializer(Agent& agent);

    /*
     * Creates and instance of the policy class and returns a pointer to it.
     * */
    static BasePolicy* create_policy(Agent& agent);
};
