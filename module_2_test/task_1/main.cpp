#include <iostream>
#include <stack>

using namespace std;

bool compare(int n1, int n2) {
    return n1 < n2;
};

template<class T>
class BinaryTree {
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node* parent;
        explicit Node(T key_):key(key_), left(nullptr), right(nullptr), parent(nullptr){};
    };
    Node* root;
    void nodeOut(Node* node);
    bool (*compare)(T , T );
    bool isAllEqual(Node* node, T key);
    
public:
    explicit BinaryTree(bool (*compareFunc)(T , T ));
    void out();
    void add(int key);
    bool find(T t);
    bool isAllEqual();
};

template<class T>
bool BinaryTree<T>::isAllEqual() {
    if (root) {
        return isAllEqual(root, root->key);
    }
    return false;
}

template<class T>
bool BinaryTree<T>::isAllEqual(BinaryTree::Node *node, T key) {
    if (node) {
        if (node->key != key) {
            return false;
        }
    }
    if (node->left) {
        return isAllEqual(node->left, key);
    }
    if (node->right) {
        return isAllEqual(node->right, key);
    }
    return true;
}

template<class T>
void BinaryTree<T>::nodeOut(Node *node) {
    if (node == nullptr) {
        return;
    }
    nodeOut(node->left);
    cout << node->key << " ";
    nodeOut(node->right);
}

template<class T>
void BinaryTree<T>::out() {
    nodeOut(root);
}

template<class T>
BinaryTree<T>::BinaryTree(bool (*compareFunc)(T , T )) {
    root = nullptr;
    compare = compareFunc;
}

template<class T>
void BinaryTree<T>::add(int key) {
    Node* addedNode = new Node(key);
    if (root == nullptr) {
        root = addedNode;
        return;
    }
    Node* left = root->left;
    Node* right = root->right;
    Node* parent = root;
    while (true){
        if(compare(key , parent->key)) {
            if (left) {
                parent = left;
                left = parent->left;
                right = parent->right;
            }
            else{
                addedNode->parent = parent;
                parent->left = addedNode;
                break;
            }
        }
        else {
            if (right) {
                parent = right;
                left = right->left;
                right = right->right;
            }
            else {
                addedNode->parent = parent;
                parent->right = addedNode;
                break;
            }
        }
    }
}

template<class T>
bool BinaryTree<T>::find(T t) {
    Node* current = root;
    while (current && current->key != t ) {
        if(this->root == NULL) {
            return false;
        }
        if (compare(t, root->key)) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    if (current) {
        return true;
    }
    return false;
}

int main() {
    int number;
    BinaryTree<int> bTree = BinaryTree<int>(compare);
    while (cin >> number) {
        bTree.add(number);
    }
    cout << bTree.isAllEqual() << endl;
}
