#ifndef CODEGEN_H
#define CODEGEN_H

#include <vector>
#include <string>
#include <iostream>
#include "lexer.h"
using namespace std;

class CodeGenerator {
private:
    vector<string> code;  
    int tempCount;   

    string newTemp();

public:
    CodeGenerator();
    void generate(const vector<Token>& tokens);
    void printCode();
};

#endif
