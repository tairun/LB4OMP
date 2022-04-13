// -------------------------- Reinforcement Learning Extension ---------------------------------//
//  June 2022
//  Master Thesis
//  Luc Kury, <luc.kury@unibas.ch>
//  University of Basel, Switzerland
//  --------------------------------------------------------------------------------------------//

namespace defaults {
    const double SEED                   = 420.69f;

    const double ALPHA                  = 0.85f;
    const double ALPHA_MIN              = 0.10f;
    const double ALPHA_DECAY_FACTOR     = 0.90f;
    const double GAMMA                  = 0.95f;
    const double EPSILON                = 1.00f;
    const double EPSILON_MIN            = 0.10f;
    const double EPSILON_DECAY_FACTOR   = 0.90f;

    const std::string INIT_INPUT        = "zero";
    const std::string REWARD_INPUT      = "looptime";
    const std::string POLICY_INPUT      = "explore_first";

}
