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

    }

    void pop() {

    }

    T top() const {
        return T();
    }

    bool empty() const {
        return true;
    }

    int size() const {
        return 0;
    }
};


#endif //PROGRAMMINGASSIGNMENT2_ARRAYSTACK_H