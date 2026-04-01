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
    string value;
};

// Tokenizer

ArrayStack<Token> tokenize(const string& line) {
    ArrayStack<Token> tokens;
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
    int prec = 0;
    if (op == "*" || op == "/") {
        prec = 2;
    } else if (op == "+" || op == "-") {
        prec = 1;
    }
    return prec;
}

// Detection

bool isValidPostfix(const ArrayStack<Token>& tokens) {
    if (tokens.empty()) return false;
    ArrayStack<Token> tempStack1 = tokens;

    ArrayStack<Token> tempStack2;
    while (!tempStack1.empty()) {
        tempStack2.push(tempStack1.top());
        tempStack1.pop();
    }
    Token previous;
    int count = 0;

    while (!tempStack2.empty()) {
        Token current = tempStack2.top();
        tempStack2.pop();
        if (current.value == "(" || current.value == ")") {
            return false;
        }
        //not an operator + 1
        if (!isOperator(current.value)) {
            count++;
        }
        // operator - 2 + 1
        if (isOperator(current.value)) {
            count = count - 2;
            if (count < 0) {
                return false; //check if first two
            } else {
                count++;
            }
        }
        previous = current;
    }
    // check first value
    if (previous.value == "(" || previous.value == ")") {
        return false;
    }
    return count == 1;
}

bool isValidInfix(const ArrayStack<Token>& tokens) {
    if (tokens.empty()) return false;

    ArrayStack<Token> tempStack = tokens;

    Token previous;
    bool notLast = false;

    while (!tempStack.empty()) {
        Token current = tempStack.top();
        tempStack.pop();

        bool currOp = isOperator(current.value);
        bool currNum = !currOp && current.value != ")" && current.value != "(";

        if (notLast) {
            bool prevOp = isOperator(previous.value);
            bool prevNum = !prevOp && previous.value != "(" && previous.value != ")" && previous.value != "(";
            if (currOp && prevOp) return false;
            if (currNum && prevNum) return false;
        } else {
            if (currOp) return false;
        }
        previous = current;
        notLast = true;
    }
    if (isOperator(previous.value)) return false;
    return true;
}


// Conversion

ArrayStack<Token> infixToPostfix(const ArrayStack<Token>& tokens) {
    ArrayStack<Token> output;
    ArrayStack<Token> tempStack = tokens;
    ArrayStack<Token> reverseStack;
    ArrayStack<Token> Operator;
    while (!tempStack.empty()) {
        reverseStack.push(tempStack.top());
        tempStack.pop();
    }
    while (!reverseStack.empty()) {
        Token current = reverseStack.top();
        reverseStack.pop();
        // add operands directly to output queue
        if (!isOperator(current.value) && current.value != "(" && current.value != ")") {
            output.push(current);
        } else if (current.value == "(") {
            // left parenthesis push onto operator stack
            Operator.push(current);
        } else if (isOperator(current.value)) {
            // pop operators from stack to output queue if higher or equal precedence then current operator
            while (!Operator.empty() && precedence(Operator.top().value) >= precedence(current.value)) {
                output.push(Operator.top());
                Operator.pop();
            }
            Operator.push(current);
        } else if (current.value == ")"){
            Token top;
            while (!Operator.empty() && Operator.top().value != "(") {
                output.push(Operator.top());
                Operator.pop();
            }
            Operator.pop();
        } else {
            cout << "ERROR - none of the cases" << endl;
        }
    }

    while (!Operator.empty()) {
        Token current = Operator.top();
        output.push(current);
        Operator.pop();
    }
    return output;
}

// Evaluation

double evalPostfix(const ArrayStack<Token>& tokens) {
    ArrayStack<double> stack;
    ArrayStack<Token> tempStack = tokens;
    ArrayStack<Token> reverseStack;
    ArrayStack<double> Numbers;
    double result;

    while (!tempStack.empty()) {
        reverseStack.push(tempStack.top());
        tempStack.pop();
    }
    while (!reverseStack.empty()) {
        Token current = reverseStack.top();
        reverseStack.pop();
        Token next;
        double num1;
        double num2;
        if (!isOperator(current.value)) {
            double currNum = std::stod(current.value);
            Numbers.push(currNum);
        } else {
            // if it's an operator look at previous two numbers
            num1 = Numbers.top();
            Numbers.pop();
            num2 = Numbers.top();
            Numbers.pop();
        }
        if (current.value == "+") {
            result = num2 + num1;
            Numbers.push(result);
        } else if (current.value == "-") {
            result = num2 - num1;
            Numbers.push(result);
        } else if (current.value == "*") {
            result = num2 * num1;
            Numbers.push(result);
        } else if (current.value == "/") {
            result = num2 / num1;
            Numbers.push(result);
        }
    }
    return Numbers.top();
}

// Main

int main() {

    cout << "Enter line with spaces between numbers/operators" << endl;

    string line;
    getline(cin, line);

    ArrayStack<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        ArrayStack<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        postfix.printStack();
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }
    return 0;
}
