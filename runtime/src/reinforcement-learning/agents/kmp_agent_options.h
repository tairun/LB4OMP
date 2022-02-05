#include <string>
#include "../thirdparty/json.hpp"

class AgentOptions {
public:
    static json parse_options(std::string config_path);

    ~AgentOptions();

private:
    AgentOptions() {}
};
