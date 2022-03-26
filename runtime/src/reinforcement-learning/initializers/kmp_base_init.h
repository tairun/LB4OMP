class BaseInit
{
public:
    static void init(int* data, int size);
    static void init(double* data, int size);
    static void init(double** data, int num_actions, int num_states);
};
