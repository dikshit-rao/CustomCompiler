#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <vector>
#include <string>
using namespace std;

// Simple optimizer that removes redundant assignments
class Optimizer {
public:
    vector<string> optimize(const vector<string>& code);
    void printOptimized(const vector<string>& optimizedCode);
};

void optimizeCode(); // function wrapper for main.cpp

#endif
