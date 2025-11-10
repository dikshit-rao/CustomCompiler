#include "../include/parser.h"
#include <iostream>
using namespace std;

Parser::Parser(const vector<Token>& toks) : tokens(toks), pos(0) {}

Token Parser::peek() {
    return (pos < tokens.size()) ? tokens[pos] : Token{UNKNOWN, ""};
}

Token Parser::get() {
    return (pos < tokens.size()) ? tokens[pos++] : Token{UNKNOWN, ""};
}

void Parser::error(const string& msg) {
    cout << "[Syntax Error] " << msg << endl;
    exit(1);
}

void Parser::parseProgram() {
    cout << "Parsing Program...\n";
    while (pos < tokens.size()) {
        parseStatement();
    }
    cout << "Parsing completed successfully!\n";
}

void Parser::parseStatement() {
    Token t = peek();
    if (t.type == KEYWORD && t.value == "let")
        parseDeclaration();
    else if (t.type == IDENTIFIER)
        parseAssignment();
    else if (t.type == KEYWORD && t.value == "print")
        parsePrint();
    else if (t.type == KEYWORD && t.value == "if")
        parseIf();
    else
        error("Unexpected token: " + t.value);
}

void Parser::parseDeclaration() {
    get(); // 'let'
    Token id = get();
    if (id.type != IDENTIFIER) error("Expected variable name after 'let'");
    Token eq = get();
    if (eq.value != "=") error("Expected '=' after variable name");
    parseExpression();
    Token semi = get();
    if (semi.value != ";") error("Missing ';' at end of declaration");
}

void Parser::parseAssignment() {
    get(); // identifier
    Token eq = get();
    if (eq.value != "=") error("Expected '=' in assignment");
    parseExpression();
    Token semi = get();
    if (semi.value != ";") error("Missing ';' in assignment");
}

void Parser::parsePrint() {
    get(); // 'print'
    Token lpar = get();
    if (lpar.value != "(") error("Expected '(' after 'print'");
    parseExpression();
    Token rpar = get();
    if (rpar.value != ")") error("Expected ')' after expression");
    Token semi = get();
    if (semi.value != ";") error("Missing ';' after print statement");
}

void Parser::parseIf() {
    get(); // 'if'
    Token lpar = get();
    if (lpar.value != "(") error("Expected '(' after 'if'");
    parseExpression();
    Token rpar = get();
    if (rpar.value != ")") error("Expected ')' after condition");
    Token lbrace = get();
    if (lbrace.value != "{") error("Expected '{' after if condition");

    while (peek().value != "}") parseStatement();
    get(); // consume '}'
}

void Parser::parseExpression() {
    Token t = get();
    if (t.type != IDENTIFIER && t.type != NUMBER)
        error("Expected identifier or number in expression");

    while (peek().value == "+" || peek().value == "-" || peek().value == "*" ||
           peek().value == "/" || peek().value == "<" || peek().value == ">") {
        get(); // operator
        Token nxt = get();
        if (nxt.type != IDENTIFIER && nxt.type != NUMBER)
            error("Invalid operand in expression");
    }
}
