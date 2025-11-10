#ifndef CODEGEN_H
#define CODEGEN_H

#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"
using namespace std;

class CodeGenerator {
private:
    vector<string> code;  // stores generated IR code
    int tempCount;        // for creating temporary variables

    string newTemp();     // generates t1, t2, t3, etc.

public:
    CodeGenerator();
    void generate(const vector<Token>& tokens);
    void printCode();
};

#endif
