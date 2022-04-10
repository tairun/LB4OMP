enum InitType
{
    ZERO = 0,
    RANDOM = 1,
    OPTIMISTIC = 2,
};

static std::unordered_map<std::string, InitType> InitTable = {
        {"zero", InitType::ZERO},
        {"random", InitType::RANDOM},
        {"optimistic", InitType::OPTIMISTIC}
};