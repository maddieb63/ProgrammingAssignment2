//
// Created by maddie on 3/24/2026.
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
        topIndex++;
        data.push_back(item);
    }

    void pop() {
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

    }

    bool empty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }

    void printStack() const {
        for (int i =0; i <= topIndex; i++) {
            std::cout << data[i].value << " ";
        }
        std::cout << std::endl;
    }

};


#endif //PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H