#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

ArrayStack<Token> tokenize(const string& line) {
    ArrayStack<Token> tokens;
    //for value in tokens:

    // TODO
    // break the input string into tokens
    // include in instructions to put spaces between characters - can find that way - loop from space to space?
        // double digits would be easier
        // parentheses too?
        // put into previously empty array
        // returns tokens as value or array?
            // tokens is a vector!
            // vectors have built in functions
    string current = "";

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            Token token;
            token.value = current;
            tokens.push(token);
            current = "";
        } else {
            current += line[i];
        }
    }
    // last value
    Token token;
    token.value = current;
    tokens.push(token);


    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    // this is precedence of operators
    // parentheses come first then rest of PEMDAS
    // gives indexes priority? - indexes hold multiple values?
    // return type is int

    return 0;
}

// Detection

bool isValidPostfix(const ArrayStack<Token>& tokens) {
    // TODO
    // search for operators - use isOperator
    // if at the end post fix
    // if parentheses - throw error
    // Ex: A B C * + D +     =     A + B * C + D
    return false;
}

bool isValidInfix(ArrayStack<Token>& tokens) {
    // TODO
    // normal operations
    // computer doesn't understand precedence from parentheses or operators?
    if (tokens.empty()) return false;

    // check last index
    Token top = tokens.top();
    if (isOperator(top.value)) return false;
    tokens.pop();

    while (!tokens.empty()) {
        Token current = tokens.top();
        tokens.pop();
        Token previous = tokens.top();
        if (isOperator(previous.value) && isOperator(current.value)) {
            return false;
        }
    }

    return true;
}

// Conversion

ArrayStack<Token> infixToPostfix(const ArrayStack<Token>& tokens) {
    ArrayStack<Token> output;
    // TODO
    // order determined by position - put highest precedence first
    return output;
}

// Evaluation

double evalPostfix(const ArrayStack<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    // solve expression
    // take values from stack use to operate
    // pop one at a time and do something to current total value?
        // first in first out - keep in mind
        // reverse order from vector?

    return 0.0;
}

// Main

int main() {

    cout << "Testing Print - Enter line " << endl;

    string line;
    getline(cin, line);

    ArrayStack<Token> tokens = tokenize(line);
    tokens.printStack();

    /*
    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
    */
}
