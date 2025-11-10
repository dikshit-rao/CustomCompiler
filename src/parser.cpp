#include "../include/parser.h"
#include "../include/lexer.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ✅ Global definitions (only one copy)
vector<Token> tokens;
int currentIndex = 0;

// ✅ Safely get current token
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

// ✅ Move to next token
void nextToken() {
    if (currentIndex < (int)tokens.size()) {
        currentIndex++;
    }
}


// Utility checks
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

// Simple error function
void error(const string &msg) {
    cout << "[Syntax Error] " << msg << endl;
}

// Forward declaration
bool parseExpression();

// Parse parenthesis and arithmetic expressions recursively
bool parseExpression() {
    Token t = currentToken();

    // Case 1: Expression starts with '('
    if (t.value == "(") {
        nextToken(); // consume '('
        if (!parseExpression()) return false;
        if (currentToken().value != ")") {
            error("Missing closing parenthesis");
            return false;
        }
        nextToken(); // consume ')'
    }
    // Case 2: Identifier or number
    else if (isIdentifier(t) || isNumber(t)) {
        nextToken();
    }
    else {
        error("Invalid operand in expression");
        return false;
    }

    // If there's an operator, recursively parse next expression
    if (isOperator(currentToken())) {
        nextToken();
        if (!parseExpression()) return false;
    }

    return true;
}

// Parse assignment statements
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

    nextToken(); // consume '='
    if (!parseExpression()) return false;

    if (currentToken().value != ";") {
        error("Missing ';' after assignment");
        return false;
    }

    nextToken(); // consume ';'
    return true;
}

// Parse 'let' declarations
bool parseDeclaration() {
    nextToken(); // consume 'let'
    if (!parseAssignment()) return false;
    return true;
}

// Parse print statement
bool parsePrint() {
    nextToken(); // consume 'print'
    if (currentToken().value != "(") {
        error("Expected '(' after print");
        return false;
    }

    nextToken(); // consume '('
    if (!isIdentifier(currentToken())) {
        error("Expected identifier inside print()");
        return false;
    }

    nextToken(); // consume identifier
    if (currentToken().value != ")") {
        error("Expected ')' after identifier in print()");
        return false;
    }

    nextToken(); // consume ')'
    if (currentToken().value != ";") {
        error("Missing ';' after print statement");
        return false;
    }

    nextToken(); // consume ';'
    return true;
}

// Parse if statement
bool parseIf() {
    nextToken(); // consume 'if'
    if (currentToken().value != "(") {
        error("Expected '(' after if");
        return false;
    }

    nextToken(); // consume '('
    if (!parseExpression()) return false;

    if (currentToken().value != ")") {
        error("Expected ')' after condition");
        return false;
    }

    nextToken(); // consume ')'
    if (currentToken().value != "{") {
        error("Expected '{' to start if block");
        return false;
    }

    nextToken(); // consume '{'
    while (currentToken().value != "}" && currentToken().type != UNKNOWN) {
        if (isKeyword(currentToken(), "let")) {
            if (!parseDeclaration()) return false;
        } else if (isKeyword(currentToken(), "print")) {
            if (!parsePrint()) return false;
        } else {
            error("Invalid statement inside if block");
            return false;
        }
    }

    if (currentToken().value != "}") {
        error("Expected '}' at end of if block");
        return false;
    }

    nextToken(); // consume '}'
    return true;
}

// Parse the entire program
bool parseProgram() {
    cout << "Parsing Program..." << endl;

    currentIndex = 0;

    while (currentIndex < (int)tokens.size()) {
        Token t = currentToken();

        if (isKeyword(t, "let")) {
            if (!parseDeclaration()) return false;
        } 
        else if (isKeyword(t, "if")) {
            if (!parseIf()) return false;
        } 
        else if (isKeyword(t, "print")) {
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
