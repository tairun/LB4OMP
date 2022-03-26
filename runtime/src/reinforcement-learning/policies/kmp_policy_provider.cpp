#include "kmp_policy_type.h"
#include "kmp_policy_provider.h"
#include "kmp_epsilon_greedy_policy.h"
#include "kmp_forced_exploration_policy.h"
#include "kmp_softmax_policy.h"

BasePolicy *PolicyProvider::get_policy(PolicyType type)
{
    switch (type) {
        case (PolicyType::EPSILON_GREEDY):
            return new EpsilonGreedyPolicy();
            break;
        case (PolicyType::FORCED_EXPLORATION):
            return new ForcedExplorationPolicy();
            break;
        case (PolicyType::SOFTMAX):
            return new SoftmaxPolicy();
            break;
        default:
            std::cout << "[Reinforcement Learning] Unknown policy type specified" << std::endl;
    }
}