// Author: Caden Kroonenberg
// Date: Oct. 20, 2021
#ifndef MY_BINARY_HEAP
#define MY_BINARY_HEAP

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename Comparable>
class myBinaryHeap {
    private:
    int m_size;                     // Number of elements in heap
    std::vector<Comparable> array;  // Heap array

    void buildHeap() {
        for(int i = m_size/2; i > 0; i--) {
            percolateDown(i);
        }
    }

    void percolateDown(int hole) {
        int child;
        Comparable tmp = std::move(array[hole]);
        for(; hole*2 <= m_size; hole = child) {
            child = hole*2;
            if(child != m_size && array[child+1] < array[child]) {
                ++child;
            }
            if(array[child] < tmp) {
                array[hole] = std::move(array[child]);
            } else {
                break;
            }
        }
        array[hole] = std::move(tmp);
    }

    public:
    explicit myBinaryHeap(int capacity = 100) {
        m_size = 0;
        array.reserve(capacity);
    }

    explicit myBinaryHeap(const std::vector<Comparable> & items) : array(items.size() + 10), m_size{items.size()} {
        for(int i = 0; i < items.size(); i++) {
            array[i+1] = items[i];
        }
        buildHeap();
    }

    bool isEmpty() const {
        return m_size == 0;
    }

    const Comparable & findMin() const {
        if(isEmpty()) {
            throw std::underflow_error("Error: findMin() called on empty heap");
        }
        return array[1];
    }
    
    void insert(const Comparable & x) {
        if(m_size == array.size() - 1) {
            array.resize(array.size()*2);
        }
        // Percolate up
        int hole = ++m_size;
        Comparable copy = x;

        array[0] = std::move(copy);
        for(;x < array[hole/2]; hole/=2) {
            array[hole] = std::move(array[hole/2]);
        }
        array[hole] = std::move(array[0]);
    }

    void insert(Comparable && x) {
        if(m_size == array.size() - 1) {
            array.resize(array.size()*2);
        }
        // Percolate up
        int hole = ++m_size;
        Comparable copy = x;

        array[0] = std::move(copy);
        for(;x < array[hole/2]; hole/=2) {
            array[hole] = std::move(array[hole/2]);
        }
        array[hole] = std::move(array[0]);
    }

    void deleteMin() {
        if(isEmpty()) {
            throw std::underflow_error("Error: deleteMin() called on empty heap");
        }
        array[1] = std::move(array[m_size--]);
        percolateDown(1);
    }

    void deleteMin(Comparable & minItem) {
        if(isEmpty()) {
            throw std::underflow_error("Error: deleteMin() called on empty heap");
        }
        minItem = std::move(array[1]);
        array[1] = std::move(array[m_size--]);
        percolateDown(1);
    }

    void makeEmpty() {
        while(!isEmpty()) {
            deleteMin();
        }
    }

    void PrintHeap(void) {
        for (int i = 1; i <= m_size; i++) {
            std::cout << array[i] << " ";
        }
        //std::cout << "\n";
    }

    myBinaryHeap& merge(myBinaryHeap& rhs) {
        for (int i = 1; i <= rhs.m_size; i++) {
            array[m_size + i] = rhs.array[i];
        }
        m_size+=rhs.m_size;
        buildHeap();
        return *this;
    }

    bool verifyHeapProperty(void) {
        for(int i = 1; i <= m_size; i++) {
            if(i*2 <= m_size) {
                if(array[i] > array[i*2]) {
                    return false;
                }
            }
            if((i*2)+1 <= m_size) {
                if(array[i] > array[(i*2)+1]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool increaseKey(const int p, const int d) {
        if(p < 1 || p > m_size) {
            return false;
        }
        array[p]+=d;
        buildHeap();
        return true;
    }
    bool decreaseKey(const int p, const int d) {
        if(p < 1 || p > m_size) {
            return false;
        }
        array[p]-=d;
        buildHeap();
        return true;
    }
};

#endif // MY_BINARY_HEAP