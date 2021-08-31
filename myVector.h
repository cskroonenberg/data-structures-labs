/**
 * @author Caden Kroonenberg
 * @file myVector.h
 * @date August 30, 2021
 * @brief Header file for vector ADT
 **/
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <algorithm>
#include <vector>

template <typename Object>
class myVector
{
    static const int SPARE_CAPACITY = 16;

    private:
    int m_size;
    int m_capacity;
    Object* m_objects;

    public:

    /**
    * @brief Constructor
    * @pre initSize > 0
    * @post myVector ADT is created with size initSize
    * @param initSize, initial size of myVector ADT
    */
    explicit myVector(int initSize = 0) { // Initial size defaults to 0
        m_size = initSize;
        m_capacity = initSize + SPARE_CAPACITY; // ?
        m_objects = new Object[m_capacity];
    }

    /**
    * @brief Copy constructor for STL vector
    * @pre lhs myVector ADT is being constructed with the values of rhs STL vector
    * @post lhs myVector ADT is created with the same values as rhs STL vector
    * @param rhs, STL vector which will provide initial values for lhs myVector ADT
    */
    myVector(const std::vector<Object>& data) {
        m_size = data.size();
        m_capacity = data.capacity();
        m_objects = new Object[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_objects[i] = data[i];
        }
    }

    /**
    * @brief Copy constructor
    * @pre lhs myVector ADT is being constructed with the values of rhs myVector ADT
    * @post lhs myVector ADT is created with the same values as rhs myVector ADT
    * @param rhs, myVector ADT which will provide initial values for lhs myVector ADT
    */
    myVector(const myVector &rhs ) {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_objects = new Object[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_objects[i] = rhs.m_objects[i];
        }
    }

    /**
    * @brief Copy assignment operator
    * @pre rhs is lvalue myVector ADT
    * @post lhs myVector ADT is constructed with the same values as rhs myVector ADT
    * @param rhs, myVector ADT which will provide values for lhs myVector ADT
    */
    myVector & operator= (const myVector &rhs) {
        myVector copy = rhs;
        std::swap(*this, copy); // Swap values of rhs and lhs
        return *this;
    }

    /**
    * @brief Destructor
    * @pre myVector ADT is being popped off call stack
    * @post myVector ADT is destructed
    */
    ~myVector() {
        delete[] m_objects;
    }

    /**
    * @brief Move constructor
    * @pre rhs is rvalue vector ADT
    * @post myVector ADT is constructed with values of rhs
    * @param rhs, lvalue myVector ADT which provides initial values for lhs myVector ADT
    */
    myVector(myVector &&rhs) {
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_objects = rhs.m_objects;

        rhs.m_size = 0;
        rhs.m_capacity = 0;
        rhs.m_objects = nullptr;
    }

    /**
    * @brief Move assignment operator
    * @pre lhs is vector ADT, rhs is rvalue vector ADT
    * @post lhs is assigned values of rhs; rhs is 'removed' from memory
    * @param rhs, lvalue myVector ADT which provides values for lhs myVector ADT
    */
    myVector & operator= (myVector &&rhs) {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_objects, rhs.m_objects);

        return *this;
    }

    /**
    * @brief Update vector capacity
    * @post Capacity is updated if newCapacity < m_size
    * @param newCapacity, updated capacity value
    */
    void reserve(int newCapacity) {
        // Return if size is too large for new capacity
        if(newCapacity < m_size) {
            return;
        }

        // Move object array into an array of updated capacity
        Object *newArr = new Object[newCapacity];
        for (int i = 0; i < m_size; i++) {
            // Assign new array values without using extra memory
            newArr[i] = std::move(m_objects[i]);
        }

        m_capacity = newCapacity;
        std::swap(m_objects, newArr);
        delete[] newArr;
    }

    /**
    * @brief Update vector size
    * @post Size is updated; Capacity is updated if size > capacity
    * @param newSize, updated size value
    */
    void resize(int newSize) {
        if (newSize > m_capacity) {
            reserve(newSize*2);
        }
        m_size = newSize;
    }

    /**
    * @brief Retrieve value at index
    * @param index, index of requested value
    * @return Value at index
    */
    Object& operator[](int index) {
        return m_objects[index];
    }

    /**
    * @brief Retrieve value at index
    * @param index, index of requested value
    * @return Value at index
    */
    const Object& operator[](int index) const {
        return m_objects[index];
    }

    /**
    * @return True if myVector is empty
    */
    bool empty() const {
        return (size() == 0);
    }

    /**
    * @return Size of myVector
    */
    int size() const {
        return m_size;
    }

    /**
    * @return Capacity of myVector
    */
    int capacity() const {
        return m_capacity;
    }

    /**
    * @brief Append rvalue x to the end of myVector
    */
    void push_back(const Object& x) {
        if (m_size == m_capacity) {
            reserve(2*m_capacity+1);
        }
        m_objects[m_size++] = x;
    }

    /**
    * @brief Append lvalue x to the end of myVector
    */
    void push_back(Object&& x) {
        if (m_size == m_capacity) {
            reserve(2*m_capacity+1);
        }
        m_objects[m_size++] = std::move(x);
    }

    /**
    * @brief Remove a value from the end of myVector
    */
    void pop_back() {
        m_size--;
    }

    /**
    * @brief Append a myVector ADT to the end of currect myVector ADT
    * @param data, myVector object to append to back of current myVector object
    * @return Current myVector ADT
    */
    myVector<Object>& append(const myVector<Object>& data) {
        // Reserve space if necessary
        if (m_size + data.size() >= m_capacity) {
            reserve( 2 * ( m_size + data.size() ) );
        }
        // Append new values
        for (int i = 0; i < data.size(); i++) {
            m_objects[m_size++] = data.m_objects[i];
        }
        return *this;
    }

    /**
    * @return Last object in myVector
    */
    const Object& back() const {
        return m_objects[m_size - 1];
    }

    typedef Object* iterator;
    typedef const Object* const_iterator;

    /**
    * @return Pointer to the beginning of myVector
    */
    iterator begin() {
        return &m_objects[0];
    }

    /**
    * @return Const pointer to the beginning of myVector
    */
    const_iterator begin() const {
        return &m_objects[0];
    }
    
    /**
    * @return Pointer to the end of myVector
    */
    iterator end() {
        return &m_objects[size()];
    }

    /**
    * @return Const pointer to the end of myVector
    */
    const_iterator end() const {
        return &m_objects[size()];
    }

};
#endif // MY_VECTOR_H