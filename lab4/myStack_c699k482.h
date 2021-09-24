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
    Object* m_arr;

    void init(const int& size) {
        m_arr = new Object[size];
        m_capacity = size;
        m_top = -1;
    }

    void reserve(const int & capacity) {
        if(capacity < size()) {
	    //std::cout<<"CAP < SIZE \n";
            return;
        }
	//std::cout << "new cap: " << capacity << std::endl;
	Object* newArr = new Object[capacity];
	for(int i = 0; i < m_capacity; i++) {
	    newArr[i] = m_arr[i];
	}
	std::swap(m_arr, newArr);
        m_capacity = capacity;
	delete[] newArr;
	//std::cout << "return from reserve\n";
    }

    public:
    myStack(const int& size) {
        init(size);
    }

    myStack(const myStack<Object> & rhs) {
        m_capacity = rhs.m_capacity;
        m_top = rhs.m_top;
	m_arr = new Object[m_capacity];
        for(int i = 0; i < m_capacity; i++) {
            m_arr[i] = rhs.m_arr[i];
        }
    }

    myStack& operator= ( const myStack & rhs) {
        myStack copy = rhs;
        std::swap(*this, copy); // Swap values of rhs and lhs
        return *this;
    }

    myStack(const myStack<Object> && rhs) {
        m_capacity = rhs.m_capacity;
        m_arr = rhs.m_arr;
        m_top = rhs.m_top;

        rhs.m_top = 0;
        rhs.m_capacity = 0;
        rhs.m_arr = nullptr;
      }

    myStack & operator= (myStack &&rhs) {
        std::swap(m_top, rhs.m_top);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_arr, rhs.m_arr);

        return *this;
    }

    ~myStack() {
	delete[] m_arr;
    }

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
	//std::cout<<"cap: "<< m_capacity << " | m_top: " << m_top << " m_arr[m_top]: " << m_arr[m_top] << std::endl;
        if(m_top == m_capacity-1) {
            reserve((m_top+2)*2); // TODO: Reserve
        }
        m_top++;
        m_arr[m_top] = rhs;
    }

    Object& top(void) {
        if(empty()) {
            throw(std::runtime_error("Cannot access top member of empty stack"));
        }
        return m_arr[m_top];
    }

    int size(void) const {
        return m_top + 1;
    }

    int capacity(void) const {
        return m_capacity;
    }
};
#endif // MY_STACK_H
