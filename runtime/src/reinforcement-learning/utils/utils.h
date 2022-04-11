#include <string>

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