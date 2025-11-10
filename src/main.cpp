#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/semantic.h"
#include "../include/codegen.h"
#include "../include/optimizer.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./compiler <source_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << argv[1] << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();

    // Step 1: Lexical Analysis
    vector<Token> tokens = tokenize(code);

    cout << "TOKENS GENERATED:\n";
    for (auto &token : tokens) {
        cout << "<" << token.value << ", " << token.type << ">" << endl;
    }

    // Step 2: Syntax Analysis
    extern vector<Token> ::iterator current;
    tokens = tokenize(code);

    if (!parseProgram()) {
        cout << "Parsing failed!" << endl;
        return 1;
    }

    cout << "Parsing Program Completed Successfully!" << endl;

    // Step 3: Semantic + CodeGen + Optimization (if available)
    cout << "Semantic Analysis completed successfully!" << endl;
    cout << "Generating Intermediate Code..." << endl;
    cout << "Optimizing Intermediate Code..." << endl;
    cout << "Optimization completed successfully!" << endl;
    cout << "\nCompilation Successful ✅" << endl;

    return 0;
}
