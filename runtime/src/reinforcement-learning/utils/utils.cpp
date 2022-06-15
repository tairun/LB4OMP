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

void read_env_enum(const char* var_name, DecayType& target)
{
    if (std::getenv(var_name) != nullptr)
    {
        std::string str = std::string(std::getenv(var_name));
        target = DecayTable.at(str);
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

/*
 * Searches for the best action (index) for a given state (using the Q-Values).
 * */
int argmax(double** ref_table, int next_state, int size)
{
    int best_index = 0;
    double best_current = -9999;

    for (int i = 0; i < size; i++)
    {
        std::cout << "[Utils::argmax] Index ... " << i << std::endl;
        if (ref_table[next_state][i] > best_current)
        {
            best_current = ref_table[next_state][i];
            best_index = i;
        }
    }
    return best_index;
}

void dumpArray2D(double** ref_table, int row, int col) {
    std::cout << "[Utils::dumpArray2D] Hi from dump " << std::endl;
    //std::cout << "[" << std::flush;

    int i, j;

    for (i = 0; i < row; i++) {
        //std::string line_start = i == 0 ? "[" : " [";
        //std::cout << line_start << std::flush;
        for (j = 0; j < col; j++) {
            std::cout << ref_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    //std::cout << "]" << std::endl;
}