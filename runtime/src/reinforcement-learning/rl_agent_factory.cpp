#include <string>

#include ""
#include "rl_agent_factory.hpp"
#include "rl_agent.hpp"
#include "agent_type.hpp"
#include "q_learner_old.hpp"
#include "agents/agent_options.hpp"

rl_agent *rl_agent_factory::create_agent(json *agent_options) {
    rl_agent *agent;

    switch (agent_options->type) {
        case 1: // Q-Learner Old
            agent = new q_learner_old()
            break;
        default:
            std::out << "Reinforcement Learning: Unknown agent type specified in options json: " << agent_options->type std::endl;
    }

    return agent;
}
