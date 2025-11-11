#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <unordered_map>
#include <vector>
#include "lexer.h"
#include "parser.h"
using namespace std;

class SemanticAnalyzer {
private:
    unordered_map<string, bool> symbolTable;

public:
    void analyze(const vector<Token>& tokens);
};

#endif
