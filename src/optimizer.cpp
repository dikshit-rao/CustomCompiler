#include "../include/optimizer.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> Optimizer::optimize(const vector<string>& code) {
    vector<string> optimized;
    unordered_map<string, string> computed; // map: variable → value

    for (const string& line : code) {
        // skip empty lines
        if (line.empty()) continue;

        // Basic dead code elimination
        size_t eq = line.find('=');
        if (eq != string::npos) {
            string lhs = line.substr(0, eq - 1);
            string rhs = line.substr(eq + 1);

            // Trim spaces (basic)
            lhs.erase(remove(lhs.begin(), lhs.end(), ' '), lhs.end());
            rhs.erase(remove(rhs.begin(), rhs.end(), ' '), rhs.end());

            if (computed[lhs] == rhs) {
                // Redundant assignment, skip
                continue;
            }
            computed[lhs] = rhs;
        }

        optimized.push_back(line);
    }
    return optimized;
}

void Optimizer::printOptimized(const vector<string>& optimizedCode) {
    cout << "\nOptimized Intermediate Code:\n";
    for (const auto& line : optimizedCode) {
        cout << line << endl;
    }
}

// Function called from main.cpp
void optimizeCode() {
    cout << "Performing simple optimization (dead code removal)..." << endl;
    Optimizer opt;

    // Example: In a real compiler, you'd pass generated code here.
    vector<string> dummy = {
        "t1 = 5 + 3",
        "x = t1",
        "x = t1",  // redundant
        "PRINT x"
    };

    vector<string> optimized = opt.optimize(dummy);
    opt.printOptimized(optimized);
}
