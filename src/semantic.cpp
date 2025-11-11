#include "../include/semantic.h"
#include "../include/lexer.h"
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Use the same global tokens vector declared in parser.cpp
extern vector<Token> tokens;

// Symbol table to store declared variable names
unordered_set<string> declaredVars;

bool performSemanticAnalysis() {
    declaredVars.clear();
    bool success = true;

    for (size_t i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];

        // Handle declarations
        if (t.type == KEYWORD && t.value == "let") {
            if (i + 1 < tokens.size() && tokens[i + 1].type == IDENTIFIER) {
                string var = tokens[i + 1].value;

                // Check if already declared
                if (declaredVars.count(var)) {
                    cout << "[Semantic Error] Variable '" << var << "' redeclared." << endl;
                    success = false;
                } else {
                    declaredVars.insert(var);
                }
            }
        }

        // Handle identifier usages (not after 'let')
        if (t.type == IDENTIFIER) {
            if (i > 0 && tokens[i - 1].value == "let") continue; // skip declaration
            if (!declaredVars.count(t.value)) {
                cout << "[Semantic Error] Variable '" << t.value << "' used before declaration." << endl;
                success = false;
            }
        }
    }

    if (success)
        cout << "Semantic Analysis completed successfully!" << endl;
    else
        cout << "Semantic Analysis found errors." << endl;

    return success;
}
