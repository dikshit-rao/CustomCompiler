#include "../include/codegen.h"
#include "../include/lexer.h"

#include <stack>

CodeGenerator::CodeGenerator() : tempCount(0) {}

string CodeGenerator::newTemp() {
    return "t" + to_string(++tempCount);
}

void CodeGenerator::generate(const vector<Token>& tokens) {
    cout << "Generating Intermediate Code...\n";

    stack<string> operands;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& t = tokens[i];

        // Declaration: let a = <expr>;
        if (t.type == KEYWORD && t.value == "let") {
            string var = tokens[i + 1].value;
            string next = tokens[i + 3].value;

            if (tokens[i + 3].type == IDENTIFIER || tokens[i + 3].type == NUMBER) {
                string temp = newTemp();
                code.push_back(temp + " = " + next);
                code.push_back(var + " = " + temp);
            }

            // Handle simple operations like: let b = a + 5;
            if (tokens[i + 4].type == OPERATOR) {
                string left = tokens[i + 3].value;
                string op = tokens[i + 4].value;
                string right = tokens[i + 5].value;
                string temp = newTemp();
                code.push_back(temp + " = " + left + " " + op + " " + right);
                code.push_back(var + " = " + temp);
            }
        }

        // Assignment: a = a + 1;
        if (t.type == IDENTIFIER && tokens[i + 1].value == "=") {
            string var = t.value;
            string left = tokens[i + 2].value;

            if (tokens[i + 3].type == OPERATOR) {
                string op = tokens[i + 3].value;
                string right = tokens[i + 4].value;
                string temp = newTemp();
                code.push_back(temp + " = " + left + " " + op + " " + right);
                code.push_back(var + " = " + temp);
            } else {
                string temp = newTemp();
                code.push_back(temp + " = " + left);
                code.push_back(var + " = " + temp);
            }
        }

        // Print: print(a);
        if (t.type == KEYWORD && t.value == "print") {
            string var = tokens[i + 2].value;
            code.push_back("PRINT " + var);
        }
    }
}

void CodeGenerator::printCode() {
    cout << "\nGenerated Intermediate Code (3-Address Form):\n";
    for (const string& line : code) {
        cout << line << endl;
    }
}
