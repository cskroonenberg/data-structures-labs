/**
 * @author Caden Kroonenberg
 * @file myList.h
 * @date September 7, 2021
 * @brief Header file for linked list ADT
 **/
#ifndef MY_LIST_H
#define MY_LIST_H

#include<algorithm>
template <typename Object>
class myList {
    private:
        struct Node {
            Object m_data;
            Node *m_prev;
            Node *m_next;

            Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr) {
                m_data = d;
                m_prev = p;
                m_next = n;
            }

            Node(Object &&d, Node *p = nullptr, Node *n = nullptr) {
                m_data = std::move(d);
                m_prev = p;
                m_next = n;
            }
        };

    public:
        class const_iterator {
            public:
            const_iterator() {
                m_current = nullptr;
            }

            const Object& operator* () const {
                return retrieve();
            }

            const_iterator& operator++ () {
                m_current = m_current->m_next;
                return *this;
            }

            const_iterator operator++ (int) {
                const_iterator old = *this;
                ++(*this);
                return old;
            }

            const_iterator& operator-- () {
                m_current = m_current->m_prev;
                return *this;
            }

            const_iterator operator-- (int) {
                const_iterator old = *this;
                --(*this);
                return old;
            }

            bool operator== (const const_iterator &rhs) const {
                return m_current == rhs.m_current;
            }

            bool operator!= (const const_iterator &rhs) const {
                return !(*this == rhs);
            }

            protected:
            Node* m_current;

            Object& retrieve() const {
                return m_current->m_data;
            }

            const_iterator(Node *p) {
                m_current = p;
            }

            friend class myList<Object>;
        };

    class iterator : public const_iterator {
        public:
        iterator() {}
        
        Object& operator* () {
            return const_iterator::retrieve();
        }

        const Object& operator* () const {
            return const_iterator::operator*();
        }

        iterator& operator++ () {
            this->m_current = this->m_current->m_next;
            return *this;
        }

        iterator operator++ (int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- () {
            this->m_current = this->m_current->m_prev;
            return *this;
        }

        iterator operator-- (int) {
            iterator old = *this;
            --(*this);
            return old;
        }

        protected:

        iterator(Node *p) : const_iterator{ p } {}

        friend class myList<Object>;
    };

    public:
    myList() {
        init();
    }

    myList(const myList &rhs) {
        init();
        for(auto &x : rhs) {
            push_back(x);
        }
    }

    ~myList() {
        clear();
        delete m_head;
        delete m_tail;
    }

    myList & operator= (const myList &rhs) {
        myList copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    myList(myList &&rhs) {
        m_size = rhs.m_size;
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        rhs.m_size = 0;
        rhs.m_head = nullptr;
        rhs.m_tail = nullptr;
    }

    myList & operator= (myList &&rhs) {
        std::swap(m_size, rhs.m_size);
        std::swap(m_head, rhs.m_head);
        std::swap(m_tail, rhs.m_tail);
        return *this;
    }

    void reverselist(void) {
        myList<Object>* old = new myList<Object>;
        while(!empty()) {
            old->push_front(front());
            pop_front();
        }
        while(!old->empty()) {
            push_front(old->back());
            old->pop_back();
        }
        delete old;
    }

    myList<Object>& appendList(const myList<Object>& linked_list) {
        for(const_iterator itr = linked_list.begin(); itr != linked_list.end(); itr++) {
            push_back(*itr);
        }
        return *this;
    }

    bool swapAdjElements(iterator &itr) {
        if (itr.m_current->m_next == nullptr) {
            return false;
        }
        Object temp = itr.m_current->m_data;
        itr.m_current->m_data = itr.m_current->m_next->m_data;
        itr.m_current->m_next->m_data = temp;
        return true;
    }

    iterator begin() {
        return m_head->m_next;
    }

    const_iterator begin() const{
        return m_head->m_next;
    }

    iterator end() {
        return m_tail;
    }

    const_iterator end() const{
        return m_tail;
    }

    int size() const {
        return m_size;
    }

    bool empty() const {
        return size() == 0;
    }

    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

    Object & front() {
        return *begin();
    }

    const Object & front() const {
        return *begin();
    }

    Object & back() {
        return *--end();
    }

    const Object& back() const {
        return *--end();
    }

    void push_front(const Object &x) {
        insert(begin(), x);
    }

    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x) {
        insert(end(), x);
    }

    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }

    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.m_current;
        m_size++;
        return {p->m_prev = p->m_prev->m_next = new Node{x, p->m_prev, p}};
    }

    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.m_current;
        m_size++;
        return{p->m_prev = p->m_prev->m_next = new Node{std::move(x), p->m_prev, p}};
    }

    iterator erase(iterator itr) {
        Node *p = itr.m_current;
        iterator retVal{p->m_next};
        p->m_prev->m_next = p->m_next;
        p->m_next->m_prev = p->m_prev;
        delete p;
        m_size--;
        return retVal;
    }

    iterator erase(iterator from, iterator to) {
        for(iterator itr = from; itr != to;) {
            itr = erase(itr);
        }
        return to;
    }

    private:
    int m_size;
    Node *m_head;
    Node *m_tail;

    void init() {
        m_size = 0;
        m_head = new Node;
        m_tail = new Node;
        m_head->m_next = m_tail;
        m_tail->m_prev = m_head;
    }
};
#endif // MY_LIST_H