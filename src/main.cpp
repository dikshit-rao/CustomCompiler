#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/lexer.h"
#include "../include/parser.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./compiler <source_file>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << argv[1] << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();

    vector<Token> tokens = tokenize(code);

    cout << "TOKENS GENERATED:\n";
    for (auto& token : tokens) {
        cout << "<" << token.value << ", ";
        switch (token.type) {
            case KEYWORD: cout << "KEYWORD"; break;
            case IDENTIFIER: cout << "IDENTIFIER"; break;
            case NUMBER: cout << "NUMBER"; break;
            case OPERATOR: cout << "OPERATOR"; break;
            case SEPARATOR: cout << "SEPARATOR"; break;
            case COMMENT: cout << "COMMENT"; break;
            case UNKNOWN: cout << "UNKNOWN"; break;
        }
        cout << ">\n";
    }

    Parser parser(tokens);
    parser.parseProgram();

    return 0;
}
