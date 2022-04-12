#include <iostream>

#include "utils.h"


std::string read_env_string(const char* var_name)
{
    if (std::getenv(var_name) != nullptr)
    {
        return std::getenv(var_name);
    }
    else
    {
        std::cout << "[read_env_string] Couldn't read '" << var_name << "' from env." << std::endl;
        return nullptr;
    }
}

void read_env_string(const char* var_name, std::string& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        target = std::string(std::getenv(var_name));
    }
    else
    {
        std::cout << "[read_env_string] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}

void read_env_double(const char* var_name, double& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        target = std::stod(std::getenv(var_name));
    }
    else
    {
        std::cout << "[read_env_double] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}
