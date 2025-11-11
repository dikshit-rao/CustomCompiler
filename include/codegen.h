#ifndef CODEGEN_H
#define CODEGEN_H

#include "lexer.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class CodeGenerator {
    int tempCount;
    vector<string> code;

public:
    CodeGenerator();
    string newTemp();
    void generate(const vector<Token>& tokens);
    void printCode();
};

#endif
