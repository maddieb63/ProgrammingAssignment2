//
// Created by maddi on 3/24/2026.
//

#ifndef PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H
#define PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H

#include<vector>
#include <stdexcept>

template<typename T>

class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& item) {
        if // stack is not full (!isFull)
        // increment top index number and make index[] equal to item
        // size limit?

    }

    void pop() {
        if // stack is not empty (!isEmpty)
        // first in - first out
        // decrement top
        // size should automatically get smaller if top moves?
    }

    T top() const {
        if // if not empty returns top data
        return T();
    }

    bool empty() const {
        // only full if the top value is -1
        return true;
    }

    int size() const {
        // return number of indexes + 1 for index 0
        return 0;
    }
};


#endif //PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H