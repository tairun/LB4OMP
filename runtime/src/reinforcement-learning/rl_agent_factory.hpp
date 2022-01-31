#pragma once

#include <string>

#include "agents/rl_agent.hpp"
#include "agent_type.hpp"

class rl_agent_factory {
public:
  /* Destructor */
  ~rl_agent_factory() = default;

  /* Creates and return a pointer to a learning agent with the specified type
   * and options. */
  static RLAgent *create_agent(nlohmann::json *agent_options);

private:
    /* Disallow creating an instance of this object */
    rl_agent_factory() = default;
};