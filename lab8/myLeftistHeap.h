// Author: Caden Kroonenberg
// Date: 10-27-21

#ifndef MY_LEFTIST_HEAP
#define MY_LEFTIST_HEAP

#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename Comparable>
class myLeftistHeap {
    public:
    myLeftistHeap() : root{nullptr} {}

    myLeftistHeap( const myLeftistHeap & rhs ) : root{nullptr} {
        root = clone(rhs.root);
    }

    myLeftistHeap( myLeftistHeap && rhs ) : root{nullptr} {
        root = clone(rhs.root);
    }

    ~myLeftistHeap() {
        makeEmpty();
    }

    bool isEmpty( ) const {
        return root == nullptr;
    }

    const Comparable & findMin( ) const {
        return root->element;
    }

    void insert( const Comparable & x ) {
        root = merge(new LeftistNode{ x }, root);
    }

    void insert( Comparable && x ) {
        root = merge(new LeftistNode{ x }, root);
    }

    void deleteMin( ) {
        if(isEmpty()) {
            throw std::underflow_error("ERROR: Attempted deleteMin() on empty heap");
        }
        LeftistNode *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    void deleteMin( Comparable & minItem ) {
        minItem = findMin();
        deleteMin();
    }

    void makeEmpty() {
        while(!isEmpty()) {
            deleteMin();
        }
    }

    void merge( myLeftistHeap & rhs ) {
        if(this == &rhs) {
            return;
        }
        root = merge(root, rhs.root);
        rhs.root = nullptr;
    }

    void printPreOrder() {
        printPreOrder(root);
        std::cout << std::endl;
    }

    private:
    struct LeftistNode
    {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode( const Comparable& e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element { e }, left{ lt }, right{ rt }, npl{ np } {}
            
        LeftistNode( Comparable&& e, LeftistNode *lt = nullptr,
                    LeftistNode *rt = nullptr, int np = 0)
            : element{ std::move(e) }, left{ lt }, right{ rt }, npl{ np } {}
    };
    LeftistNode *root;

    LeftistNode * merge( LeftistNode *h1, LeftistNode *h2 ) {
        if(h1 == nullptr) {
            return h2;
        }
        if(h2 == nullptr) {
            return h1;
        }
        if(h1->element < h2->element) {
            return merge1(h1,h2);
        } else {
            return merge1(h2,h1);
        }
    }

    LeftistNode * merge1( LeftistNode *h1, LeftistNode *h2 ) {
        if(h1->left == nullptr) {
            h1->left = h2;
        } else {
            h1->right = merge(h1->right, h2);
            if(h1->left->npl < h1->right->npl) {
                swapChildren(h1);
            }
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }

    void swapChildren( LeftistNode *t ) {
        LeftistNode* temp = t->right;
        t->right = t->left;
        t->left = temp;
    }

    LeftistNode * clone( LeftistNode *t ) const {
        if(t == nullptr) {
            return nullptr;
        } else {
            return new LeftistNode{t->element, clone(t->left), clone(t->right)};
        }
    }

    void printPreOrder(LeftistNode* t) {
        if(t != nullptr) {
            std::cout << t->element << " ";
            printPreOrder(t->left);
            printPreOrder(t->right);
        }
    }
};

#endif // MY_LEFTIST_HEAP