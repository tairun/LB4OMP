#pragma once

/* Struct to manage data of the reinforcement learning agent */
class RLInfo {
public:

    RLInfo(int states, int actions) {
        count = new int[states];
        qvalue = new double*[states];

        for (int i = 0; i < states; i++) {
            qvalue[i] = new double[actions];
        }

        for (int s = 0; s < states; s++)
            for (int a = 0; a < actions; a++) {
                count[a] = 0;
                qvalue[s][a] = -299.0;
        }

        alpha = std::stod(std::getenv("KMP_RL_ALPHA"));
        gamma = std::stod(std::getenv("KMP_RL_GAMMA"));
    }

    int state{0};
    int action{0};
    int trialstate{0};
    int* count;

    double lowTime{-99.0}, highTime{-999.0};
    double** qvalue;
    double bestqvalue{0.0};

    double alpha{};
    double gamma{};

private:
};
