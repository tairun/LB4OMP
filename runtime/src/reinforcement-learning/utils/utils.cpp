// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

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

int read_env_int(const char* var_name, int rdefault)
{
    if (std::getenv(var_name) != nullptr)
    {
       return std::stoi(std::getenv(var_name));
    }
    else
    {
        std::cout << "[read_env_int] Couldn't read '" << var_name << "' from env. Using provided default value." << std::endl;
        return rdefault;
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

void read_env_enum(const char* var_name, RewardType& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        std::string str = std::string(std::getenv(var_name));
        target = RewardTable.at(str);
    }
    else
    {
        std::cout << "[read_env_double] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}

void read_env_enum(const char* var_name, InitType& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        std::string str = std::string(std::getenv(var_name));
        target = InitTable.at(str);
    }
    else
    {
        std::cout << "[read_env_enum] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}

void read_env_enum(const char* var_name, PolicyType& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        std::string str = std::string(std::getenv(var_name));
        target = PolicyTable.at(str);
    }
    else
    {
        std::cout << "[read_env_enum] Couldn't read '" << var_name << "' from env. Using default." << std::endl;
    }
}

double sum(const double* array, int length)
{
    double sum = 0.0f;

    for (int i = 0; i < length; i++)
        sum += array[i];

    return sum;
}
