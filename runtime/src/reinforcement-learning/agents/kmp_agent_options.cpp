#include <string>

#include "kmp_agent_options.h"
#include "../thirdparty/json.hpp"

int AgentOptions::parse_options(std::string config_path) {
    std::ifstream options_file(config_path)
    json options = json::parse(options_file);
}