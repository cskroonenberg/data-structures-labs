#include <iostream>
#include "myHashTable.h"
#include <string>

class HashEntry
{
    private:
       std::string key_;
       size_t value_;
    public:
        HashEntry()
        {
        
        }
        HashEntry(const std::string& key, const size_t& val)
        {
          this->key_ = key;
          this->value_ = val;
        }
      
        const std::string getKey() const
        {
            return this->key_;
        }
        size_t getValue()
        {
          return this->value_;
        }

        bool operator ==(const HashEntry& p) const
        {
            return (this->key_ == p.key_);
        }

  };

int main() {
    std::cout << "Hello, World!\n";
    myHashTable<HashEntry> myTable;
    HashEntry myEntry("0swq4pge36", myTable.strToHashValue("0swq4pge36"));
    int hashValue = myEntry.getValue();
    std::cout << "hash?: " << hashValue << "\n";
    std::cout << "hash mod: " << hashValue % myTable.m_lists.size() << "\n";
    std::cout << "insert?: " << myTable.insert(myEntry) << "\n";
    return 0;
    std::cout << "contains entry?: " << myTable.contains(myEntry) << "\n";
}