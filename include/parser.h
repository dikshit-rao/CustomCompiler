#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"
using namespace std;

class Parser {
private:
    vector<Token> tokens;
    size_t pos;

    Token peek();
    Token get();
    void error(const string& msg);

public:
    Parser(const vector<Token>& toks);
    void parseProgram();

private:
    void parseStatement();
    void parseDeclaration();
    void parseAssignment();
    void parsePrint();
    void parseIf();
    void parseExpression();
};

#endif
