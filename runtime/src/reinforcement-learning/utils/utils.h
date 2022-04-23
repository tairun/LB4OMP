#include <string>

#include "../rewards/kmp_reward_type.h"
#include "../policies/kmp_policy_type.h"
#include "../initializers/kmp_init_type.h"

#pragma once


/*
* Reads the environment variable with the name 'var_name' and parses it as a string.
* */
std::string read_env_string(const char* var_name);

/*
 * Reads the environment variable with the name 'var_name' and parses it as a string.
 * */
void read_env_string(const char* var_name, std::string& target);

/*
 * Reads the environment variable with the name 'var_name' and parses it as a double.
 * */
void read_env_double(const char* var_name, double& target);

void read_env_enum(const char* var_name, RewardType& target);
void read_env_enum(const char* var_name, InitType& target);
void read_env_enum(const char* var_name, PolicyType& target);

/*
 * Returns the sum of values (double) in an array.
 * */
double sum(const double* array, int length);