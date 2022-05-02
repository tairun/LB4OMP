#pragma once

typedef struct {
    int n;
    int p;
    int autoSearch;
    int cDLS;           // current DLS
    int bestDLS;        // Best DLS
    int searchTrials;   // number of trials to find the best DLS
    int cChunk;         // current chunk size
    int bestChunk;      // chunk size of the best DLS technique
    double cTime;       // current DLS time
    double bestTime;    // loop time of the best DLS
    double cLB;         // load imbalance of the current DLS
    double bestLB;      // load imbalance of the best DLS
    double cRobust;     // current Robustness
} LoopData;