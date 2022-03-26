#include "kmp_policy_type.h"
#include "kmp_base_policy.h"

class PolicyProvider
{
private:
    PolicyProvider();
public:
    static BasePolicy* get_policy(PolicyType type);
    ~PolicyProvider();
};