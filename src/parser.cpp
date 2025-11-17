#include "../include/parser.h"
#include "../include/lexer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

extern vector<Token> tokens;

int currentIndex = 0;


Token currentToken() {
    if (currentIndex < (int)tokens.size()) {
        return tokens[currentIndex];
    } else {
        Token t;
        t.value = "";
        t.type = UNKNOWN;
        return t;
    }
}

void nextToken() {
    if (currentIndex < (int)tokens.size()) {
        currentIndex++;
    }
}

bool isIdentifier(const Token &t) {
    return t.type == IDENTIFIER;
}

bool isNumber(const Token &t) {
    return t.type == NUMBER;
}

bool isOperator(const Token &t) {
    return t.type == OPERATOR;
}

bool isKeyword(const Token &t, const string &word) {
    return t.type == KEYWORD && t.value == word;
}

void error(const string &msg) {
    cout << "[Syntax Error] " << msg << endl;
}

bool parseExpression();


bool parseExpression() {
    Token t = currentToken();

    if (t.value == "(") {
        nextToken();
        if (!parseExpression()) return false;
        if (currentToken().value != ")") {
            error("Missing closing parenthesis");
            return false;
        }
        nextToken();
    }
    else if (isIdentifier(t) || isNumber(t)) {
        nextToken();
    }
    else {
        error("Invalid operand in expression");
        return false;
    }

    if (isOperator(currentToken())) {
        nextToken();
        if (!parseExpression()) return false;
    }

    return true;
}


bool parseAssignment() {
    Token id = currentToken();
    if (!isIdentifier(id)) {
        error("Expected identifier in assignment");
        return false;
    }

    nextToken();
    if (currentToken().value != "=") {
        error("Expected '=' in assignment");
        return false;
    }

    nextToken();
    if (!parseExpression()) return false;

    if (currentToken().value != ";") {
        error("Missing ';' after assignment");
        return false;
    }

    nextToken();
    return true;
}

bool parseDeclaration() {
    nextToken(); 
    if (!parseAssignment()) return false;
    return true;
}

bool parsePrint() {
    nextToken();

    if (currentToken().value != "(") {
        error("Expected '(' after show");
        return false;
    }

    nextToken();
    if (!isIdentifier(currentToken())) {
        error("Expected identifier inside show()");
        return false;
    }

    nextToken();
    if (currentToken().value != ")") {
        error("Expected ')' after identifier in show()");
        return false;
    }

    nextToken();
    if (currentToken().value != ";") {
        error("Missing ';' after show statement");
        return false;
    }

    nextToken();
    return true;
}


bool parseIf() {
    nextToken();
    if (currentToken().value != "(") {
        error("Expected '(' after if");
        return false;
    }

    nextToken();
    if (!parseExpression()) return false;

    if (currentToken().value != ")") {
        error("Expected ')' after condition");
        return false;
    }

    nextToken();
    if (currentToken().value != "{") {
        error("Expected '{' to start if block");
        return false;
    }

    nextToken();
    while (currentToken().value != "}" && currentToken().type != UNKNOWN) {
        if (isKeyword(currentToken(), "say")) {
            if (!parseDeclaration()) return false;
        } 
        else if (isKeyword(currentToken(), "show")) {
            if (!parsePrint()) return false;
        } 
        else {
            error("Invalid statement inside if block");
            return false;
        }
    }

    if (currentToken().value != "}") {
        error("Expected '}' at end of if block");
        return false;
    }

    nextToken(); 
    return true;
}


bool parseProgram() {
    cout << "Parsing Program..." << endl;

    currentIndex = 0;

    while (currentIndex < (int)tokens.size()) {
        Token t = currentToken();

        if (isKeyword(t, "say")) {
            if (!parseDeclaration()) return false;
        }
        else if (isKeyword(t, "if")) {
            if (!parseIf()) return false;
        }
        else if (isKeyword(t, "show")) {
            if (!parsePrint()) return false;
        }
        else if (t.type == UNKNOWN) {
            break;
        }
        else {
            error("Unexpected token: " + t.value);
            return false;
        }
    }

    cout << "Parsing completed successfully!" << endl;
    return true;
}
