#include "../include/lexer.h"
#include <cctype>
#include <unordered_set>

vector<Token> tokenize(const string& code) {
    vector<Token> tokens;
    unordered_set<string> keywords = {"let", "if", "print"};
    unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>'};
    unordered_set<char> separators = {'(', ')', '{', '}', ';', ','};

    size_t i = 0;
    while (i < code.size()) {
        if (isspace(code[i])) { i++; continue; }

        // Comments
        if (code[i] == '/' && i + 1 < code.size() && code[i + 1] == '/') {
            while (i < code.size() && code[i] != '\n') i++;
            continue;
        }

        // Identifiers / Keywords
        if (isalpha(code[i])) {
            string word;
            while (i < code.size() && (isalnum(code[i]) || code[i] == '_')) {
                word += code[i++];
            }
            if (keywords.count(word))
                tokens.push_back({KEYWORD, word});
            else
                tokens.push_back({IDENTIFIER, word});
        }

        // Numbers
        else if (isdigit(code[i])) {
            string num;
            while (i < code.size() && isdigit(code[i])) {
                num += code[i++];
            }
            tokens.push_back({NUMBER, num});
        }

        // Operators
        else if (operators.count(code[i])) {
            string op(1, code[i]);
            tokens.push_back({OPERATOR, op});
            i++;
        }

        // Separators
        else if (separators.count(code[i])) {
            string sep(1, code[i]);
            tokens.push_back({SEPARATOR, sep});
            i++;
        }

        // Unknowns
        else {
            string unk(1, code[i]);
            tokens.push_back({UNKNOWN, unk});
            i++;
        }
    }

    return tokens;
}
