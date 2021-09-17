/**
 * @author Caden Kroonenberg
 * @file myStack.h
 * @date September 15, 2021
 * @brief Header file for stack ADT
 **/

#ifndef MY_STACK_H
#define MY_STACK_H

#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename Object>
class myStack {
    private:
    int m_capacity;
    int m_top;
    std::vector<Object> m_vector;

    void init(const int& size) {
        m_vector.reserve(size);
        m_capacity = size;
        m_top = -1;
    }

    void reserve(const int & capacity) {
        if(capacity < size()) {
            return;
        }
        m_capacity = capacity;
        m_vector.reserve(capacity);
        m_vector.resize(capacity);
    }

    public:
    myStack(const int& size) {
        init(size);
    }

    myStack(const myStack<Object> & rhs) {
        reserve(rhs.capacity());
        m_top = rhs.m_top;
        for(int i = 0; i < m_capacity; i++) {
            m_vector[i] = rhs.m_vector[i];
        }
    }

    myStack& operator= ( const myStack & rhs) {
        myStack copy = rhs;
        std::swap(*this, copy); // Swap values of rhs and lhs
        return *this;
    }

    myStack(const myStack<Object> && rhs) {
        m_capacity = rhs.m_capacity;
        m_vector = rhs.m_vector;
        m_top = rhs.m_top;

        rhs.m_top = 0;
        rhs.m_capacity = 0;
        // TODO: Deal w vector??
    }

    myStack & operator= (myStack &&rhs) {
        std::swap(m_top, rhs.m_top);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_vector, rhs.m_vector);

        return *this;
    }

    ~myStack() {}

    bool empty(void) const {
        return m_top == -1;
    }

    void clear(void) {
        while(!empty()) {
            pop();
        }
    }

    void pop(void) {
        if(empty()) {
            throw(std::runtime_error("ERROR: Cannot pop an empty stack"));
        }
        m_top--;
    }

    void push(const Object & rhs) {
        if(m_top == m_capacity-1) {
            reserve((m_top+2)*2); // TODO: Reserve
        }
        m_top++;
        m_vector[m_top] = rhs;
    }

    Object& top(void) {
        if(empty()) {
            throw(std::runtime_error("Cannot access top member of empty stack"));
        }
        return m_vector[m_top];
    }

    int size(void) const {
        return m_top + 1;
    }

    int capacity(void) const {
        return m_capacity;
    }
};
#endif // MY_STACK_H