// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#include <cmath>
#include <random>

#include "kmp_rl_agent.h"
#include "kmp_chunk_learner.h"
//#include "../initializers/kmp_base_init.h"
#include "../initializers/kmp_zero_init.h"


// public
ChunkLearner::ChunkLearner(int num_states, int num_actions, LoopData* stats) :
              RLAgent(num_states, num_actions, "Chunk Learner")
{
    /*
     * Make sure, length of chunk size array is odd.
     * [ 1, .. , .. , golden chunk , .. , .. , n/p ]
     * Initialization according to @method get_chunks
     * */

    int array_size = is_even(num_actions) ? num_actions + 1 : num_actions;
    state_space  = array_size; // Q-Table will be bigger, we could make it arbitrarily big --> performance issues
    action_space = array_size; // Q-Table will be bigger, we could make it arbitrarily big --> performance issues

    ZeroInit::init(chunk_sizes, state_space);
    //chunk_sizes = new int[array_size];

    // Initialize first dimension of table
    ZeroInit::init(q_table, state_space, action_space);
    //q_table = new double *[state_space];

    current_state = get_chunks(chunk_sizes, array_size, stats->n, stats->p);

    /*
    // Initialize second dimension of table
    for (int i = 0; i < state_space; i++) {
        q_table[i] = new double[action_space];
    }

    // Initialize values of table
    for (int s = 0; s < state_space; s++)
    {
        for (int a = 0; a < action_space; a++)
            q_table[s][a] = 0.0f;
    }
    */
}

// private
int ChunkLearner::policy(int episode, int timestep, RLAgent& agent)
{
    int action_index = RLAgent::policy(episode, timestep, agent.get_table());
    int chunk_size = chunk_sizes[action_index];

    return chunk_size;
}

void ChunkLearner::update(int next_state, int next_action, double reward_value)
{
    int best_action = arg_max(q_table, next_state);
    q_table[current_state][current_action] += alpha * (reward_value + gamma * Q(next_state, best_action) - Q(current_state, current_action));
}

// static
int ChunkLearner::golden_chunk_size(int n, int p)
{
    int mul = log2( n / p) * 0.618;        // Use golden ratio
    int chunk_size = n / ((2 << mul) * p);

    return chunk_size;
}

bool ChunkLearner::is_even(int x)
{
    return x % 2 == 0;
}

int ChunkLearner::get_chunks(int* array, int size, int n, int p)
{
    int idx, dist = n/p, gold = golden_chunk_size(n, p);
    int min = 1, max = n/p, delta = (max - min) / (size - 1);

    for (int i = 0; i < size; i++)
    {
        int val = min + i * delta;

        if (std::abs(gold - val) < dist)
        {
            dist = std::abs(gold - val);
            idx = i;
        }
        array[i] = min + i * delta;
    }

    return idx;
}
