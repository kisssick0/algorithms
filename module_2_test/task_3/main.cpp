#include <iostream>
#include <string>

#define XVALUE 11;

using namespace std;

struct Node {
    string product_name;
    int color;
    int size;
    Node() {
    }
    Node(string name, int col, int siz): product_name(name), color(col), size(siz){};
    bool operator==(const Node& rh) {
        return (this->product_name == rh.product_name && this->color == rh.color && this->size == rh.size);
    };
};

int gorner(string str){
    int hash;
    for (char c: str) {
        hash = 11 * hash + c;
    }
    return hash;
}

int gorner(Node node) {
    return gorner(node.product_name);
}

template<class T>
class HashTable {
private:
    struct Cell {
        T value;
        bool isDeleted;
        bool isNull;
        Cell(const T& value_): value(value_), isDeleted(false), isNull(false) {};
        Cell():isNull(true), isDeleted(false) {};
    };
    double rehashKoeff;
    Cell* table;
    int (*hashFunction)(T);
    int arrSize;
    int realTableSize;
    void rehash();

public:
    explicit HashTable(int (*hashFunction)(T), double rehashKoef);
    bool add(T value);
    bool find(T value);
    bool del(T value);
    void out();
};

template<class T>
HashTable<T>::HashTable(int (*hashFunction)(T), double rehashKoef) {
    arrSize = 8;
    table = new Cell[arrSize];
    realTableSize = 0;
    hashFunction = hashFunction;
    for (int i = 0; i < arrSize; ++i) {
        table[i] = Cell();
    }
    rehashKoeff = rehashKoef;
}

template<class T>
bool HashTable<T>::add(T value) {
    if (find(value)) {
        return false;
    }
    if (realTableSize > rehashKoeff*arrSize) {
        rehash();
    }
    int index = gorner(value);
    index = index % arrSize;
    while(!table[index].isNull && !table[index].isDeleted) {
        index++;
        if(index >= arrSize) {
            index = 0;
        }
    }
    table[index].value = value;
    table[index].isNull = false;
    table[index].isDeleted = false;
    realTableSize++;
    return true;
}

template<class T>
bool HashTable<T>::find(T value) {
    int index = (gorner(value) % arrSize);
    int i = index;
    while(i < arrSize) {
        if (!table[i].isNull && !table[i].isDeleted && table[i].value == value) {
            return true;
        }
        i++;
        if(i == index)
            break;
        if (i == arrSize)
            i = 0;
    }
    return false;
}

template<class T>
bool HashTable<T>::del(T value) {
    int index = (gorner(value) % arrSize);
    int i = index;
    while(i < arrSize) {
        if (!table[i].isNull && !table[i].isDeleted && (table[i].value == value)) {
            table[i].isDeleted = true;
            realTableSize--;
            return true;
        }
        i++;
        if(i == index)
            break;
        if (i == arrSize)
            i = 0;
    }
    return false;
}

template<class T>
void HashTable<T>::rehash() {
    int newArrSize = arrSize*2;
    realTableSize = 0;
    Cell* newArr = new Cell[newArrSize];
    swap(newArr, table);
    for (int i = 0; i < arrSize; ++i) {
        if (!newArr[i].isNull){
            if(!newArr[i].isDeleted){
                add(newArr[i].value);
            }
        }
    }
    arrSize = newArrSize;
    delete[] newArr;
}

template<class T>
void HashTable<T>::out() {
    for (int i = 0; i < arrSize; ++i) {
        cout << table[i].value << " deleted: " << table[i].isDeleted << " null:" << table[i].isNull << endl;
    }
}


int main() {
    HashTable<Node> hTable = HashTable<Node>(gorner, (0.75));
    char operationType;
    string str;
    int color, size;
    bool isOk;
    while(cin >> operationType >> str >> color >> size) {
        switch (operationType) {
            case '+':
                isOk = hTable.add(Node(str, color, size));
                break;
            case '-':
                isOk = hTable.del(Node(str, color, size));
                break;
            case '?':
                isOk = hTable.find(Node(str, color, size));
                break;
            default:
                isOk = false;
        }
        if(isOk)
            cout << "OK" << endl;
        else
            cout << "FAIL" << endl;
    }
    return 0;
}
