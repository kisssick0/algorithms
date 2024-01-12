#include <iostream>
#include <stack>

using namespace std;

bool compare(int n1, int n2) {
    return n1 < n2;
};

template<class T>
class BinaryTree {
public:
    explicit BinaryTree(bool (*compareFunc)(T , T ));
    void out();
    void add(int key);
    
private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node* parent;
        explicit Node(int key_):key(key_), left(nullptr), right(nullptr), parent(nullptr){};
    };
    Node* root;
    void nodeOut(Node* node);
    bool (*compare)(T , T );
};

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
    stack<Node*> stack;
    Node* current = root;
    while (current || !stack.empty()) {
        if (current) {
            stack.push(current);
            current=current->left;
        }
        else {
            current = stack.top();
            stack.pop();
            cout << current->key << " ";
            current = current->right;
        }
    }
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
    while (true) {
        if(compare(key , parent->key)) {
            if (left){
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

int main() {
    size_t numbersCnt;
    cin >> numbersCnt;
    BinaryTree<int> bTree = BinaryTree<int>(compare);
    for (int i = 0; i < numbersCnt; ++i) {
        int number;
        cin >> number;
        bTree.add(number);
    }
    
    bTree.out();
}
