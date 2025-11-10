#include "../include/semantic.h"
#include <iostream>
using namespace std;

void SemanticAnalyzer::analyze(const vector<Token>& tokens) {
    cout << "Performing Semantic Analysis...\n";

    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];

        // Handle declarations: let a = ...
        if (t.type == KEYWORD && t.value == "let") {
            if (i + 1 < tokens.size() && tokens[i + 1].type == IDENTIFIER) {
                string varName = tokens[i + 1].value;
                if (symbolTable.count(varName)) {
                    cout << "[Semantic Error] Variable '" << varName << "' redeclared.\n";
                    exit(1);
                } else {
                    symbolTable[varName] = true; // declared
                }
            }
        }

        // Handle variable usage
        if (t.type == IDENTIFIER) {
            // Check if it's a declaration target
            if (i > 0 && tokens[i - 1].value == "let") continue;
            // Check if it's being assigned or used
            if (!symbolTable.count(t.value)) {
                cout << "[Semantic Error] Variable '" << t.value << "' used before declaration.\n";
                exit(1);
            }
        }
    }

    cout << "Semantic Analysis completed successfully!\n";
}
