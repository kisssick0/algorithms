#include <iostream>
#include <stack>

using namespace std;

struct node {
    struct node* left;
    int data;
    struct node* right;
};

void add(struct node** root, int data) {
    if(*root == NULL) {
        (*root) = (struct node*)malloc(sizeof(node));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->data = data;
    }
    else {
        if(data < (*root)->data)
            add(&(*root)->left, data);
        else
            add(&(*root)->right, data);
    }

}

void inorder(struct node* root) {
    if(root == NULL)
        return;
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

int shortestBranch(node* root) {
    if (root == NULL) {return 0;}
    if (root->left == NULL && root->right == NULL) {
        return 1;
    } else if (root->left == NULL) {
        return 1 + shortestBranch(root->right);
    } else if (root->right == NULL) {
        return 1 + shortestBranch(root->left);
    } else {
        return 1 + min(shortestBranch(root->right), shortestBranch(root->left));
    }
}

int main() {
    struct node* root = NULL;
    int number;
    while (cin >> number) {
        add(&root, number);
    }
    cout<<endl;
    cout << shortestBranch(root) << endl;
}
