#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
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

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO
    // search for operators - use isOperator
    // if at the end post fix
    // if parentheses - throw error
    return false;
}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO
    // normal operations
    // computer doesn't understand precedence from parentheses or operators?

    return false;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    // order determined by position - put highest precedence first
    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
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
    //ArrayStack.h testing
    ArrayStack<int> stack;

    cout << "Testing " << endl;
    //push
    stack.push(4);
    stack.push(8);
    stack.push(12);
    stack.push(16);

    cout << "Top (16?) is: " << stack.top() << endl;
    cout << "Size (4?) is: " << stack.size() << endl;

    //pop
    stack.pop();
    cout << "Top (12?) is: " << stack.top() << endl;
    cout << "Size (3?) is: " << stack.size() << endl;

    //empty
    stack.empty();
    cout << "Size (0?) is: " << stack.top() << endl;


    /* string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);


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
