/*4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Требования: скорость выполнения команды - O(log n).
Формат входных данных.
Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
Формат выходных данных.
На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад).*/

#include <iostream>
#include <queue>

using namespace std;

class AVLTree {
public:
    AVLTree() { Root = NULL; }

    ~AVLTree() { while (Root) erase(Root, 0); }
    
    int addKey(int key) {
        return insert(Root, key);
    }
    
    void deleteKey(int Pos) {
        erase(Root, Pos);
    }
    
private:
    struct TNode {
        int key;
        int height;
        int size;
        TNode* left;
        TNode* right;
        TNode(int k) :key(k), height(1), size(1), left(NULL), right(NULL) {}
    };

    TNode* Root;

    int getHeight(TNode* node) {
        return node ? node->height : 0;
    }
    
    int getSize(TNode* node) {
        return node ? node->size : 0;
    }

    int B_Factor(TNode* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void fixHeight(TNode* node) {
        int hl = getHeight(node->left);
        int hr = getHeight(node->right);
        node->height = hl > hr ? hl + 1 : hr + 1;
    }

    void fixSize(TNode* node) {
        int ml = getSize(node->left);
        int mr = getSize(node->right);
        node->size = ml + mr + 1;
    }
    
    void rightRotate(TNode*& node) {
        TNode* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        fixSize(node);
        fixSize(tmp);
        node = tmp;
    }

    void leftRotate(TNode*& node) {
        TNode* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        fixSize(node);
        fixSize(tmp);
        node = tmp;
    }

    void balance(TNode*& node) {
        if (!node)
            return;
        fixHeight(node);
        fixSize(node);
        switch (B_Factor(node)) {
        case  2:
            if (B_Factor(node->right) < 0)
                rightRotate(node->right);
            leftRotate(node);
            break;
        case -2:
            if (B_Factor(node->left) > 0)
                leftRotate(node->left);
            rightRotate(node);
            break;
        }
    }

    void removeMax(TNode*& node) {
        if (!(node->left))
            node = node->right;
        else {
            removeMax(node->left);
            balance(node);
        }
    }

    int insert(TNode*& node, int k) {
        if (!node) {
            node = new TNode(k);
            return 0;
        }
        node->size++;
        int Pos = 0;
        if (k < node->key)
            Pos = getSize(node->left) + insert(node->right, k) + 1;
        else if (k > node->key)
            Pos = insert(node->left, k);
        else
            return 0;
        balance(node);
        return Pos;
    }
    
    void erase(TNode*& node, int index) {
        if (!node)
            return;
        if (index < getSize(node->left))
            erase(node->left, index);
        else if (index > getSize(node->left))
            erase(node->right, index - getSize(node->left) - 1);
        else {
            TNode* L = node->left, * right = node->right;
            delete node;
            if (!right) node = L;
            else {
                TNode* Rmax = right;
                while (Rmax->left)
                    Rmax = Rmax->left;
                removeMax(right);
                Rmax->right = right;
                Rmax->left = L;
                node = Rmax;
            }
        }
        balance(node);
    }
};

int main() {
    AVLTree* avl = new AVLTree;
    int numOfCommands, cmd, num;
    cin >> numOfCommands;
    queue<int> q;
    for (int i = 0; i < numOfCommands; i++) {
        cin >> cmd >> num;
        if (cmd == 1)
            q.push(avl->addKey(num));
        else
            avl->deleteKey(num);
    }
    delete avl;
    
    while (!q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
    return 0;
}
