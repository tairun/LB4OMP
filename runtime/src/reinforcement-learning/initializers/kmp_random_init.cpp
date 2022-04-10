#include "kmp_random_init.h"

void RandomInit::init(int* data, int size)
{
    data = new int[size];

    for (int i = 0; i < size; i++)
    {
        data[i] = 0;
    }
}

void RandomInit::init(double* data, int size)
{
    data = new double[size];

    for (int i = 0; i < size; i++)
    {
        data[i] = 0.0f;
    }
}

void RandomInit::init(double **data, int num_states, int num_actions)
{
    data = new double*[num_states];

    for (int i = 0; i < num_states; i++) {
        data[i] = new double[num_actions];
    }

    for (int s = 0; s < num_states; s++)
    {
        for (int a = 0; a < num_actions; a++)
            data[s][a] = 0.0f;
    }
}