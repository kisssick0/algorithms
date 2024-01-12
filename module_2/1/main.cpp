// Двойное хеширование

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

namespace NodeStatus {
    int data = 0;
    int del = 1;
    int empty = 2;
};

struct Hasher1 {
    unsigned int operator()(const string& str) const {
        unsigned int hash = 0;
        unsigned int hashCoeff = 7;
        for (char c: str) {
            hash = hash * hashCoeff + c;
        }
        return hash;
    }
};

struct Hasher2 {
    unsigned int operator()(const string& str) const {
        unsigned int hash = 0;
        unsigned int hashCoeff = 17;
        for (char c: str) {
            hash = hash * hashCoeff + c;
        }
        return hash;
    }
};


template<class T, class H1, class H2>
class HashTable {
public:
    explicit HashTable(const H1& _hasher1, const H2& _hasher2);
    HashTable(const HashTable& table) = delete;
    HashTable& operator=(const HashTable& table) = delete;
    ~HashTable() = default;

    bool add(const T& data){
        if (keysCount > table.size() * 3 / 4) {
            growTable();
        }
        unsigned int firstHash = hasher(data);
        unsigned int step = (hasher2(data) * 2) + 1;
        int freeSpot = -1;
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::del && freeSpot < 0) {
                freeSpot = (firstHash + i * step) % table.size();
                continue;
            }
            
            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::data && data == table[(firstHash + i * step)% table.size()].data) {
                return false;
            }

            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::empty) {
                if (freeSpot >= 0) {
                    table[freeSpot].status = NodeStatus::data;
                    table[freeSpot].data = data;
                }
                else {
                    table[(firstHash + i * step) % table.size()].status = NodeStatus::data;
                    table[(firstHash + i * step) % table.size()].data = data;
                }
                keysCount++;
                return true;
            }
        }
        
        if (freeSpot >= 0) {
            table[freeSpot].status = NodeStatus::data;
            table[freeSpot].data = data;
            keysCount++;
            return true;
        }
        return false;
    }
    
    bool has(const T& data) const {
        unsigned int firstHash = hasher(data);
        unsigned int step = (hasher2(data) * 2) + 1;
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::del) {
                continue;
            }

            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::data && data == table[(firstHash + i * step) % table.size()].data) {
                return true;
            }

            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::empty) {
                return false;
            }
        }
        return false;
    }
    
    bool del(const T& data) {
        unsigned int firstHash = hasher(data);
        unsigned int step = (hasher2(data) * 2) + 1;
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::del) {
                continue;
            }

            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::data && data == table[(firstHash + i * step)% table.size()].data) {
                table[(firstHash + i * step) % table.size()].status = NodeStatus::del;
                keysCount--;
                return true;
            }

            if (table[(firstHash + i * step) % table.size()].status == NodeStatus::empty) {
                return false;
            }
        }
        return false;
    }

private:
    H1 hasher;
    H2 hasher2;
    struct HashTableNode {
        T data;
        int status = NodeStatus::empty;
    };
    vector<HashTableNode> table;
    unsigned int keysCount;
    void growTable() {
        vector<HashTableNode> newTable(2 * table.size());
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[i].status == NodeStatus::del || table[i].status == NodeStatus::empty) {
                continue;
            }

            HashTableNode tmp = table[i];
            unsigned int newHash = hasher(tmp.data);
            unsigned int step = (hasher2(tmp.data) * 2) + 1;

            for (size_t j = 0; j < newTable.size(); ++j) {
                if (newTable[(newHash + j * step) % newTable.size()].status == NodeStatus::empty) {
                    newTable[(newHash + j * step) % newTable.size()].status = NodeStatus::data;
                    newTable[(newHash + j * step) % newTable.size()].data = tmp.data;
                    break;
                }
            }
        }
        table = move(newTable);
    };
};

template<class T, class H1, class H2>
HashTable<T, H1, H2>::HashTable(const H1& _hasher1, const H2& _hasher2) :
    hasher(_hasher1), hasher2(_hasher2), table(8), keysCount(0) {}


int main() {
    Hasher1 sh;
    Hasher2 exh;
    HashTable<string, Hasher1, Hasher2> table(sh, exh);
    char operationType = 0;
    string str;
    while( cin >> operationType >> str ) {
        switch (operationType) {
            case '+':
                cout << (table.add(str) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (table.del(str) ? "OK" : "FAIL") << endl;
                break;
            case '?':
                cout << (table.has(str) ? "OK" : "FAIL") << endl;
                break;
            default:
                assert(false);
        }
    }
    return 0;
}
