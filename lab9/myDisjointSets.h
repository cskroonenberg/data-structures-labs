// Author: Caden Kroonenberg
// Date: November 3, 2021

#ifndef MY_DISJOINT_SETS
#define MY_DISJOINT_SETS
#include <vector>

class myDisjointSets {
public:
    explicit myDisjointSets(int numElements) : s(numElements, -1), size(numElements, 1) {}

    int find(int x) const {
        if(s[x] < 0) {
            return x;       // Return x if x has no correspondant
        }
        return find(s[x]);  // Find the correspondant of x's correspondant, recursively
    }

    int find(int x) {
        if(s[x] < 0) {
            return x;               // Return x if x has no correspondant
        }
        return s[x] = find(s[x]);   // Find the correspondant of x's correspondant, recursively; set x's to the final correspondant (reducing height)
    }
    
    void unionSets(int root1, int root2) {
        if(size[root2] > size[root1]) {
            swap(root1, root2);
        }
        s[root2] = root1;                   // Update correspondant of root2
        size[root1] += size[root2];         // Update size of root1 correspondant
        size[root2] = -1;                   // Update root2 size
    }

    int getSetSize(int x) const {
        return size[find(x)];
    }

private:
    std::vector<int> s;
    std::vector<int> size;
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};

#endif // MY_DISJOINT_SETS