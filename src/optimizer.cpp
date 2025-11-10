#include "../include/optimizer.h"
#include <iostream>
#include <sstream>
#include <algorithm>

vector<string> Optimizer::optimize(const vector<string>& code) {
    cout << "\nOptimizing Intermediate Code...\n";

    vector<string> optimized;
    unordered_map<string, string> computed; // store results like "5 + 3" -> "8"

    for (string line : code) {
        // Constant folding
        stringstream ss(line);
        string t, eq, a, op, b;
        ss >> t >> eq >> a;

        if (ss >> op >> b) { // if expression exists (a + b)
            // check if both are numbers
            bool aNum = all_of(a.begin(), a.end(), ::isdigit);
            bool bNum = all_of(b.begin(), b.end(), ::isdigit);

            if (aNum && bNum) {
                int result = 0;
                if (op == "+") result = stoi(a) + stoi(b);
                else if (op == "-") result = stoi(a) - stoi(b);
                else if (op == "*") result = stoi(a) * stoi(b);
                else if (op == "/") result = stoi(b) ? stoi(a) / stoi(b) : 0;

                string folded = to_string(result);
                optimized.push_back(t + " = " + folded);
                computed[a + " " + op + " " + b] = folded;
                continue;
            }

            // Reuse previous computed expressions
            string key = a + " " + op + " " + b;
            if (computed.count(key)) {
                optimized.push_back(t + " = " + computed[key]);
                continue;
            } else {
                computed[key] = t;
            }
        }

        // Avoid duplicate temp assignments
        if (!optimized.empty() && optimized.back() == line)
            continue;

        optimized.push_back(line);
    }

    cout << "Optimization completed successfully!\n";
    return optimized;
}
