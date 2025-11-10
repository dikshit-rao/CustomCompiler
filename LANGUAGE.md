# DikLang — Language Specification (v0.1)

## Overview
DikLang is a tiny imperative language with integers, variables, expressions, print, and a basic if statement.

## Lexical Rules
- Whitespace: spaces, tabs, newlines — ignored except as separators.
- Comments: // to end of line — ignored.
- Identifiers: [A-Za-z_][A-Za-z0-9_]* (e.g., a, total_1)
- Integer literals: [0-9]+ (only non-negative integers in v0.1)
- Keywords: let, if, print
- Operators: + - * / = < > <= >= == !=
- Separators: ( ) { } ; ,

## Tokens
KEYWORD, IDENTIFIER, NUMBER, OPERATOR, SEPARATOR, COMMENT, UNKNOWN

## Grammar (EBNF)
PROGRAM := STATEMENT_LIST
STATEMENT_LIST := { STATEMENT }
STATEMENT := DECLARATION | ASSIGNMENT | PRINT_STMT | IF_STMT
DECLARATION := 'let' IDENT '=' EXPRESSION ';'
ASSIGNMENT := IDENT '=' EXPRESSION ';'
PRINT_STMT := 'print' '(' EXPRESSION ')' ';'
IF_STMT := 'if' '(' CONDITION ')' '{' STATEMENT_LIST '}'
CONDITION := EXPRESSION REL_OP EXPRESSION
REL_OP := '<' | '>' | '==' | '!=' | '<=' | '>='
EXPRESSION := TERM { ('+' | '-') TERM }
TERM := FACTOR { ('*' | '/') FACTOR }
FACTOR := IDENT | NUMBER | '(' EXPRESSION ')'

## Example
// Program in DikLang
let a = 10;
let b = a + 5;
if (b > 10) {
    print(b);
}
