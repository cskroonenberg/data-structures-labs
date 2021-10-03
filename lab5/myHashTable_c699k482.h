#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include <string>
#include <vector>
#include <list>
#include <functional>
#include <algorithm> // TODO remove
#include <cmath>

template <typename HashedObj>
class myHashTable {
    public: // TODO make private
    int m_tableSize;
    std::vector<std::list<HashedObj>> m_lists;

    int smallestPrime(int min) {
        //bool * arr[doubleSize] = {true};
        bool* arr = new bool[min*2];
        for(int i = 0; i < min*2; i++) {
            arr[i] = true;
        }
        // Denote all primes
        for(int i = 2; i <= sqrt(min*2); i++) {
            if (arr[i]) {
                for(int j = pow(i, 2); j < min*2; j += i) {
                    arr[j] = false;
                }
            }
        }
        // Find next prime
        for(int i = min; i < min*2; i++) {
            if(arr[i]) {
                delete[] arr;
                return i;
            }
        }
        delete[] arr;
        return min;
    }

    int largestPrime(int max) {
        bool* arr = new bool[max];
        for(int i = 0; i < max; i++) {
            arr[i] = true;
        }
        // Denote all primes
        for(int i = 2; i <= sqrt(max); i++) {
            if (arr[i]) {
                for(int j = pow(i, 2); j < max; j += i) {
                    arr[j] = false;
                }
            }
        }
        // Find largest prime
        int newSize = 0;
        for(int i = 0; i < max; i++) {
            if(arr[i]) {
                newSize = i;
            }
        }
        delete[] arr;
        return newSize;
    }

    void doubleTable() {
        std::vector<std::list<HashedObj>> oldLists = m_lists;

        m_lists.resize(smallestPrime(2*m_lists.size()));

        for(auto &thisList : m_lists) {
            thisList.clear();
        }

        m_tableSize = 0;

        for(auto &thisList : oldLists) {
            for(auto &x : thisList) {
                insert(x);
            }
        }
    }

    int halfTable() {
        std::vector<std::list<HashedObj>> oldLists = m_lists;

        m_lists.resize(largestPrime(2*m_lists.size()));

        for(auto &thisList : m_lists) {
            thisList.clear();
        }

        m_tableSize = 0;

        for(auto &thisList : oldLists) {
            for(auto &x : thisList) {
                insert(x);
            }
        }
    }

    double loadFactor() {
        return m_tableSize/m_lists.size();
    }

    public:
    // initialize an empty hash table with a capacity of size elements
    explicit myHashTable(int size = 101) {
        m_tableSize = 0; // TODO init to 0?
        m_lists.resize(size);
    }

    ~myHashTable() {}

    size_t strToHashValue(const std::string & str) {
        size_t hashVal = 0;

        for(char ch : str) {
            hashVal = 3 * hashVal + ch;
        }
        return hashVal;
    }

    const int DIGS = 31;
    const int mersennep = (1 << DIGS) - 1;

    int universalHash(int x, int A, int B, int M) {
        // a universal hash function as in Figure 5.51 of the textbook
        
        long long hashVal = static_cast<long long>(A)*x + B;
        hashVal = ((hashVal >> DIGS) + (hashVal & mersennep));
        if(hashVal >= mersennep) {
            hashVal -= mersennep;
        }
        return static_cast<int>(hashVal) % M;
    }

    bool contains(const HashedObj &x) {
        auto & whichList = m_lists[strToHashValue(x.getKey()) % m_lists.size()];
        return std::find(std::begin(whichList), std::end(whichList), x) != std::end(whichList);
        /*
        determine whether the element is already exists in the hash table.
        The method should return TRUE if the element exists, and FALSE if it does not exist.
        */
    }

    bool insert(const HashedObj &x) {
        auto & whichList = m_lists[strToHashValue(x.getKey()) % m_lists.size()];
        if (contains(x)) {
            return false;
        }
        whichList.push_back(x);
        
        if(++m_tableSize > m_lists.size()) {
            doubleTable();
        }
            
        return true;
        /*
        double* the vector capacity when the load factor is larger than 0.5.
            (The load factor is defined as the number of elements in the hash table over the size of the vector.)
        After doubling the table, you should perform rehashing.
        The method should return TRUE if the element is successfully inserted, and FALSE if not
            (e.g., fail to allocate more memory or the element already exists).
        (*Make sure you choose the smallest prime that is larger than the doubled
        size as the new table size.)
        */
    }

    bool insert(HashedObj &&x) {
        auto & whichList = m_lists[strToHashValue(x.getKey()) % m_lists.size()];
        if (contains(x)) {
            return false;
        }
        whichList.push_back(x);
        
        if(++m_tableSize > m_lists.size()) {
            doubleTable();
        }
            
        return true;
        /*
        double* the vector capacity when the load factor is larger than 0.5.
            (The load factor is defined as the number of elements in the hash table over the size of the vector.)
        After doubling the table, you should perform rehashing.
        The method should return TRUE if the element is successfully inserted, and FALSE if not
            (e.g., fail to allocate more memory or the element already exists).
        (*Make sure you choose the smallest prime that is larger than the doubled
        size as the new table size.)
        */
    }

    bool remove(const HashedObj &x) {
        if(!contains(x)) {
            return false;
        }
        auto &whichList = m_lists[strToHashValue(x.getKey()) % m_lists.size()];
        auto itr = find(begin(whichList), end(whichList), x);

        if(itr == end(whichList)) {
            return false;
        }

        whichList.erase(itr);
        --m_tableSize;
        if(loadFactor() < 0.25) {
            halfTable();
        }
        return true;
        // remove item

        /*
        The insertion method
        should halve* the vector capacity when the load factor is smaller than 0.25. (The load factor is
        defined as the number of elements in the hash table over the size of the vector.) After halving the
        table, you should perform rehashing. The method should return TRUE if the element is successfully
        deleted, and FALSE if not (e.g., the element does not exist). (*Make sure you choose the largest
        prime that is smaller than the halved size as the new table size.)
        */
    }

};
#endif // MY_HASH_TABLE