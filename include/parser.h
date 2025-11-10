#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "lexer.h"
using namespace std;

// ✅ Declare global tokens vector (so main.cpp can see it)
extern vector<Token> tokens;

bool parseProgram();
bool parseDeclaration();
bool parseAssignment();
bool parseExpression();
bool parseIf();
bool parsePrint();

#endif
