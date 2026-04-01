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
    int prec = 0;
    if (op == "*" || op == "/") {
        prec = 1;
    } else if (op == "+" || op == "-") {
        prec = 2;
    }
    return prec;
}

// Detection

bool isValidPostfix(const ArrayStack<Token>& tokens) {
    // TODO
    // search for operators - use isOperator
    // if at the end post fix
    // if parentheses - throw error
    // Ex: A B C * + D +        [A + B * C + D]
    if (tokens.empty()) return false;
    ArrayStack<Token> tempStack1 = tokens;
    //move into new stack to go through the other way from left to right of expression
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

    // TODO
    // normal operations
    // computer doesn't understand precedence from parentheses or operators?
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
            // check first on stack (last in equation) to see if operator -> then will go through the rest of the values
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
    // TODO
    // order determined by position - put highest precedence first
    // NOtes from Open Stack
    // when you see a parenthesis wait until ')' then pop operator
    // use stack to keep operators
    // convert input to string
    //if the token is an operand put to end of output list
    // if the token is '(' push onto stack if ')' pop until left is removed
    // if token is operator push onto stack, remove operators that higher or equal precedence and append to output

    // Shunting Yard Style:
        // moving operators to a stack and numbers to an output queue
        // Same basic steps as found from OpenStack research (no string?)
    // read left to right - reverse token stack
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
            while (precedence(Operator.top().value) >= precedence(current.value) && !Operator.empty()) {
                output.push(Operator.top());
                Operator.pop();
            }
            Operator.push(current);
        } else if (current.value == ")"){
            Token top;
            while (top.value != "(" && !Operator.empty()) {
                output.push(Operator.top());
                Operator.pop();
            }
        } else {
            cout << "ERROR - none of the cases" << endl;
        }
    }

    // pop operators from stack to output queue if higher or equal precedence then current operator
    while (!Operator.empty()) {
        Token current = Operator.top();
        output.push(current);
        Operator.pop();
    }
    // pop remaining operators from stack to the queue
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
            result = num1 + num2;
            Numbers.push(result);
        } else if (current.value == "-") {
            result = num1 - num2;
            Numbers.push(result);
        } else if (current.value == "*") {
            result = num1 * num2;
            Numbers.push(result);
        } else if (current.value == "/") {
            result = num1 / num2;
            Numbers.push(result);
        }
    }
    return Numbers.top();
}

// Main

int main() {

    cout << "Testing - Enter line with spaces between numbers/operators" << endl;

    string line;
    getline(cin, line);

    ArrayStack<Token> tokens = tokenize(line);

    if (isValidInfix(tokens)) {
        cout << "True Infix" << endl;
    } else {
        cout << "False Infix" << endl;
    }

    if (isValidPostfix(tokens)) {
        cout << "True Postfix" << endl;
    } else {
        cout << "False Postfix" << endl;
    }

    tokens.printStack();

    //cout << "Result: " << evalPostfix(tokens) << "\n";

    ArrayStack<Token> tester = infixToPostfix(tokens);
    cout << "Infix to postfix" << "\n";
    tester.printStack();

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
