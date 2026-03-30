//
// Created by maddi on 3/24/2026.
//

#ifndef PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H
#define PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H

#include<vector>
#include <stdexcept>
#include<iostream>

template<typename T>

class ArrayStack {
private:
    std::vector<T> data;
    int topIndex; // top index

public:
    ArrayStack() : topIndex(-1){}
    void push(const T& item) {
        // stack is not full (!isFull)
        // increment top index number and make index[] equal to item
        // size limit?
        topIndex++;
        data.push_back(item);
    }

    void pop() {
        // stack is not empty (!isEmpty)
        // first in - first out
        // decrement top
        // size should automatically get smaller if top moves?
        if (!empty()) {
            data.pop_back();
            topIndex--;
        } else {
            throw std::out_of_range("Stack is empty");
        }
    }

    T top() const {
        if (!empty()) {
            return data[topIndex];
        } else {
            throw std::out_of_range("Stack is empty");
        }
            // if not empty returns top data
    }

    bool empty() const {
        // only full if the top value is -1
        return topIndex == -1;
    }

    int size() const {
        // return number of indexes + 1 for index 0
        return topIndex + 1;
    }
    void printStack(const ArrayStack<T>& stack) {
        for (int i =0; i < size(); i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

};


#endif //PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H