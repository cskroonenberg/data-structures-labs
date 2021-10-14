// Author: Caden Kroonenberg
// Date: 10-13-21
#ifndef MY_BST
#define MY_BST

#include <algorithm>
#include <iostream>

template <typename Comparable>
class myBST {
    private:
    struct BinaryNode {
        Comparable element; // Node data
        BinaryNode *left;   // Left child
        BinaryNode *right;  // Right child
        BinaryNode(const Comparable &p_element, BinaryNode *lt, BinaryNode *rt) : element{p_element}, left{lt}, right{rt} {}
        BinaryNode(Comparable &&p_element, BinaryNode *lt, BinaryNode *rt) : element{std::move(p_element)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable & x, BinaryNode * & t) {
        if(t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if(x < t->element) {
            insert(x, t->left);
        } else if(t->element < x) {
            insert(x, t->right);
        }
    }

    void insert(Comparable &&x, BinaryNode* &t) {
        if(t == nullptr) {
            t = new BinaryNode(std::move(x), nullptr, nullptr);
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (t->element < x) {
            insert(std::move(x), t->right);
        }
    }

    void remove(const Comparable & x, BinaryNode * & t) {
        if(t == nullptr) {
            return;
        }
        if(x < t->element) {
            remove(x, t->left);
        } else if (t->element < x) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) { // Two children
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode* findMin(BinaryNode *t) const {
        if(t == nullptr) {
            return nullptr;
        } else if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode* findMax(BinaryNode *t) const {
        if(t != nullptr) {
            while(t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if(t == nullptr) {
            return false;
        } else if (x < t->element) {
            return contains(x, t->left);
        } else if(t->element < x) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    void makeEmpty(BinaryNode* &t) {
        if(t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    BinaryNode* clone( BinaryNode *t) const {
        if(t == nullptr) {
            return nullptr;
        } else {
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
        }
    }

    void printPreOrder(BinaryNode *t) const {
        if(t != nullptr) {
            std::cout << t->element << " ";
            printPreOrder(t->left);
            printPreOrder(t->right);
        }
    }

    void printPostOrder(BinaryNode *t) const {
        if(t != nullptr) {
            printPostOrder(t->left);
            printPostOrder(t->right);
            std::cout << t->element << " ";
        }
    }

    public:
    myBST() : root{nullptr} {}

    myBST(const myBST & rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    myBST(myBST && rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    ~myBST() {
        makeEmpty();
    }

    const Comparable & findMin() const {
        return findMin(root)->element;
    }

    const Comparable & findMax() const {
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return(root == nullptr);
    }
    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable && x) {
        insert(x, root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    myBST & operator=( const myBST & rhs) {
        return true; // TODO
    }
    myBST & operator=( myBST && rhs) {
        return true; // TODO
    }

    void printPreOrder() const {
        if(!isEmpty()) {
            printPreOrder(root);
        }
        std::cout << "\n";
    }

    void printPostOrder() const {
        if(!isEmpty()) {
            printPostOrder(root);
        }
        std::cout << "\n";
    }
};
#endif //MY_BST