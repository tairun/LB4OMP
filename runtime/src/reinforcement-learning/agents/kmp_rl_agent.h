#pragma once

#include <string>
#include <iostream>
#include "../kmp_loopdata.h"


class RLAgent {
public:
    RLAgent(int numStates, int numActions, std::string agentName) : states(numStates),
                                                                    actions(numActions),
                                                                    name(std::move(agentName)),
                                                                    reward_input("looptime")
    {
        if (std::getenv("KMP_RL_REWARD") != nullptr)
        {
            reward_input = std::getenv("KMP_RL_REWARD");
        }
        else
        {
            std::cout << "[Reinforcement Learning] Couldn't read 'KMP_RL_REWARD' from env." << std::endl;
        }

        std::cout << "[Reinforcement Learning] Configuring agent as: " << name << std::endl;
        std::cout << "[Reinforcement Learning] Using reward signal: " << reward_input << std::endl;
    }

    /* Take reward signal and perform the learning process. Returns the decisions from the agent. */
    virtual int step(int timestep, LoopData* data) = 0;

private:

protected:
    int states;
    int actions;
    std::string name;
    std::string reward_input;

    static double readEnv(const char* varName)
    {
        if (std::getenv(varName) != nullptr)
        {
            return std::stod(std::getenv(varName));
        }
        else
        {
            std::cout << "[Reinforcement Learning] Couldn't read '" << varName << "' from env." << std::endl;
        }
    }

    double getRewardSignal(LoopData* stats)
    {
        double reward_signal = 0;

        if (reward_input == "looptime")
        {
            reward_signal = stats->cTime;
        }
        else if (reward_input == "loadimbalance")
        {
            reward_signal = stats->cLB;
        }
        else if (reward_input == "robustness")
        {
            std::cout << "[Reinforcement Learning] Not yet implemented: " << reward_input << std::endl;
            reward_signal = stats->cTime;
        }
        else
        {
            std::cout << "[Reinforcement Learning] Invalid reward signal specified in env: " << reward_input << std::endl;
        }

        return reward_signal;
    }
};
