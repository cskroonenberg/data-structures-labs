/**
 * @author Caden Kroonenberg
 * @file myQueue.h
 * @date September 15, 2021
 * @brief Header file for queue ADT
 **/

#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <iostream>
template <typename Object>
class myQueue {
    private:
    int m_size;
    int m_capacity;
    int m_front;
    int m_back;
    Object* m_arr;

    void init(const int& size) {
        if (size < 2) {
            throw ("ERROR: Size must be larger than 2\n");
        }
        m_size = 0;
        m_capacity = size;
        m_front = 1;
        m_back = 0;
        m_arr = new Object[size];
    }

    void reserve(const int & capacity) {
        // Return if size is too large for new capacity
        if(capacity < m_size) {
            return;
        }

        // Move object array into an array of updated capacity
        Object *newArr = new Object[capacity];
        const int buf_size = m_size;
        for (int i = 0; i < m_size; i++) {
            newArr[i] = front();
            dequeue();
        }
        m_size = buf_size;
        m_capacity = capacity;
        std::swap(m_arr, newArr);
        m_front = 0;
        m_back = m_size - 1;
        //delete[] newArr;
    }

    public:
    myQueue(const int& size) {
        init(size);
    }

    myQueue(const myQueue<Object> & rhs) {
        reserve(rhs.capacity());
        m_size = rhs.size();
        m_front = rhs.m_front;
        m_back = rhs.m_back;
        m_arr = new Object[m_capacity];
        for(int i = 0; i < m_capacity; i++) {
            m_arr[i] = rhs.m_arr[i];
        }
    }

    myQueue& operator= ( const myQueue & rhs) {
        myQueue copy = rhs;
        std::swap(*this, copy); // Swap values of rhs and lhs
        return *this;
    }

    myQueue(const myQueue<Object> && rhs) {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_arr = rhs.m_arr;
        m_front = rhs.m_front;
        m_back = rhs.m_back;

        rhs.m_size = 0;
        rhs.m_capacity = 0;
        rhs.m_arr = nullptr;
        rhs.m_front = 0;
        rhs.m_back = 0;
    }

    myQueue & operator= (myQueue &&rhs) {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_front, rhs.m_front);
        std::swap(m_back, rhs.m_back);
        std::swap(m_arr, rhs.m_arr);

        return *this;
    }

    ~myQueue() {
        clear();
        delete[] m_arr;
    }

    bool empty(void) const {
        return m_size == 0;
    }

    void clear(void) {
        while(!empty()) {
            dequeue();
        }
    }

    void dequeue(void) {
        if(empty()) {
            throw(std::runtime_error("ERROR: Cannot dequeue an empty queue"));
        }
        if(m_front == m_capacity-1) {
            m_front = 0;
        } else {
            m_front++;
        }
        m_size--;
    }

    void enqueue(const Object & rhs) {
        //std::cout << "size: " << m_size << " | cap: " << m_capacity << " | back: " << m_back << std::endl;
        if(m_size == m_capacity) {
            reserve(m_size*2);
        }
        if(m_back == m_capacity-1) {
            m_back = 0;
        } else {
            m_back++;
        }
        m_arr[m_back] = rhs;
        m_size++;
    }

    Object& front(void) const {
        if(empty()) {
            throw(std::runtime_error("Cannot access front member of empty queue"));
        }
        return m_arr[m_front];
    }

    int size(void) const {
        return m_size;
    }

    int capacity(void) const {
        return m_capacity;
    }
};
#endif // MY_QUEUE_H