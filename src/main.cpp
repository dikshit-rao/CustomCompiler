#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/semantic.h"
#include "../include/codegen.h"
#include "../include/optimizer.h"
using namespace std;

// Declare the global tokens vector shared across modules
vector<Token> tokens;

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

    // ======== PHASE 1: LEXICAL ANALYSIS ========
    tokens = tokenize(code);

    cout << "TOKENS GENERATED:\n";
    for (auto &token : tokens) {
        cout << "<" << token.value << ", " << token.type << ">" << endl;
    }

    // ======== PHASE 2: PARSING ========
    cout << "\nParsing Program..." << endl;
    if (!parseProgram()) {
        cout << "[❌] Parsing failed!" << endl;
        return 1;
    }
    cout << "Parsing completed successfully!" << endl;

    // ======== PHASE 3: SEMANTIC ANALYSIS ========
    cout << "\nPerforming Semantic Analysis..." << endl;
    if (!performSemanticAnalysis()) {
        cout << "[❌] Semantic Analysis failed!" << endl;
        return 1;
    }

    // ======== PHASE 4: CODE GENERATION ========
cout << "\nGenerating Intermediate Code..." << endl;
CodeGenerator codegen;
codegen.generate(tokens);
codegen.printCode();

cout << "\nOptimizing Intermediate Code..." << endl;
optimizeCode();


    // ======== FINAL RESULT ========
    cout << "\n✅ Compilation Successful!" << endl;

    return 0;
}
