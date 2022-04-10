#pragma once

/*
* Reads the environment variable with the name 'var_name' and parses it as a string.
* */
std::string read_env_string(const char* var_name)
{
    if (std::getenv(var_name) != nullptr)
    {
        return std::getenv(var_name);
    }
    else
    {
        std::cout << "[AgentProvider::read_env_string] Couldn't read '" << var_name << "' from env." << std::endl;
        return nullptr;
    }
}

/*
 * Reads the environment variable with the name 'var_name' and parses it as a string.
 * */
void read_env_string(const char* var_name, std::string& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        target = std::string(std::getenv(var_name));
    }
    else
    {
        std::cout << "[Agent::read_env_string] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}

/*
 * Reads the environment variable with the name 'var_name' and parses it as a double.
 * */
void read_env_double(const char* var_name, double& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        target = std::stod(std::getenv(var_name));
    }
    else
    {
        std::cout << "[Agent::read_env_double] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}