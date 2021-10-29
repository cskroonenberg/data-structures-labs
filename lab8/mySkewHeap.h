// Author: Caden Kroonenberg
// Date: 10-27-21

#ifndef MY_SKEW_HEAP
#define MY_SKEW_HEAP

#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename Comparable>
class mySkewHeap {
    public:
    mySkewHeap() : root{nullptr} {}

    mySkewHeap( const mySkewHeap & rhs ) : root{nullptr} {
        root = clone(rhs.root);
    }

    mySkewHeap( mySkewHeap && rhs ) : root{nullptr} {
        root = clone(rhs.root);
    }

    ~mySkewHeap() {
        makeEmpty();
    }

    bool isEmpty( ) const {
        return root == nullptr;
    }

    const Comparable & findMin( ) const {
        return root->element;
    }

    void insert( const Comparable & x ) {
        root = merge(new SkewNode{ x }, root);
    }

    void insert( Comparable && x ) {
        root = merge(new SkewNode{ x }, root);
    }

    void deleteMin( ) {
        if(isEmpty()) {
            throw std::underflow_error("ERROR: Attempted deleteMin() on empty heap");
        }
        SkewNode *oldRoot = root;
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

    void merge( mySkewHeap & rhs ) {
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
    struct SkewNode
    {
        Comparable element;
        SkewNode *left;
        SkewNode *right;

        SkewNode( const Comparable& e, SkewNode *lt = nullptr,
                    SkewNode *rt = nullptr)
            : element { e }, left{ lt }, right{ rt } {}
            
        SkewNode( Comparable&& e, SkewNode *lt = nullptr,
                    SkewNode *rt = nullptr)
            : element{ std::move(e) }, left{ lt }, right{ rt } {}
    };
    SkewNode*root;

    SkewNode* merge( SkewNode *h1, SkewNode *h2 ) {
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

    SkewNode* merge1( SkewNode *h1, SkewNode *h2 ) {
        if(h1->left == nullptr) {
            h1->left = h2;
        } else {
            h1->right = merge(h1->right, h2);
        }
        return h1;
    }

    void swapChildren( SkewNode *t ) {
        SkewNode* temp = t->right;
        t->right = t->left;
        t->left = temp;
    }

    SkewNode* clone( SkewNode *t ) const {
        if(t == nullptr) {
            return nullptr;
        } else {
            return new SkewNode{t->element, clone(t->left), clone(t->right)};
        }
    }

    void printPreOrder(SkewNode* t) {
        if(t != nullptr) {
            std::cout << t->element << " ";
            printPreOrder(t->left);
            printPreOrder(t->right);
        }
    }
};

#endif // MY_SKEW_HEAP