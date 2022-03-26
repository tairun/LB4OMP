// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

#pragma once

#include "kmp_rl_agent.h"
#include "../initializers/kmp_base_init.h"


/*
 * This class implements a chunk learner which chooses from a discrete set of chunk sizes
 * directly. It uses a fixed size of possible options, oriented on the size of the DLS portfolio
 * from LB4OMP. For learning algorithm Q-Learning was selected.
 * */
class ChunkLearner : public RLAgent {
public:
    explicit ChunkLearner(int num_states, int num_actions, LoopData* stats);

    ~ChunkLearner() = default;

private:
    double** q_table{nullptr};
    int* chunk_sizes{nullptr};

    /* The policy chooses an action according to the learned experience of the agent. */
    /* Implements the Epsilon-Greedy action selection. */
    /* We need to adapt the policy function for the Chunk Learner to return the chunk size instead of the action index. */
    int policy(int episode, int timestep, RLAgent& agent);

    /* Updates the internal values of the agent. */
    void update(int next_state, int next_action, double reward_value) override;

    /* Calculates the golden chunk size using the golden ratio (0.618). Chooses a chunk size in the "middle" between 1 and n/2p. */
    static int golden_chunk_size(int n, int p);

    /* Checks if the input number is even. */
    static bool is_even(int x);

    /* Initializes array of available chunk sizes. Returns index of chunk size which is closest to the golden ratio.  */
    static int get_chunks(int* array, int size, int n, int p);
};
