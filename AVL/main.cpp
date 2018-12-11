#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
    int key;
    NODE* left;
    NODE* right;
    int height;
};

int Height(NODE* root) {
    return (!root) ? 0 : root->height;
}

NODE* NewNode(int key) {
    NODE* newNode = new NODE;
    newNode->key = key;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

void RightRotate(NODE* & root) {
    NODE* getLeft = root->left;
    NODE* subRight = getLeft->right;

    getLeft->right = root;
    root->left = subRight;

    root->height = 1 + max(Height(root->left), Height(root->right));
    getLeft->height = 1 + max(Height(getLeft->left), Height(getLeft->right));

    root = getLeft;
}

void LeftRotate(NODE* & root) {
    NODE* getRight = root->right;
    NODE* subLeft = getRight->left;

    root->right = subLeft;
    getRight->left = root;

    root->height = 1 + max(Height(root->left), Height(root->right));
    getRight->height = 1 + max(Height(getRight->left), Height(getRight->right));

    root = getRight;
}

int GetBalance(NODE* root) {
    return (!root) ? 0 : Height(root->left) - Height(root->right);
}

void Insert(NODE* & node, int key) {
    if (!node) {
        node = NewNode(key);
    }
    if (key < node->key) {
        Insert(node->left, key);
    }
    else if (key > node->key) {
        Insert(node->right, key);
    }
    else {
        return;
    }

    node->height = 1 + max(Height(node->left), Height(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && key < node->left->key) {
        return RightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return LeftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        LeftRotate(node->left);
        return RightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        RightRotate(node->right);
        return LeftRotate(node);
    }
}

void DeleteTree(NODE* root) {
    if (!root) {
        return;
    }
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
}

NODE* MinNodeFromRight(NODE* node) {
    NODE* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

void Remove(NODE* & root, int key) {
    if (!root) {
        return;
    }
    if (key < root->key) {
        Remove(root->left, key);
    }
    else if (key > root->key) {
        Remove(root->right, key);
    }
    else {
        if (!root->left) {
            NODE* temp = root->right;
            delete root;
            root = temp;
        }
        else if (!root->right) {
            NODE* temp = root->left;
            delete root;
            root = temp;
        }
        else {
            NODE* temp = MinNodeFromRight(root->right);
            root->key = temp->key;
            Remove(root->right, temp->key);
        }
    }

    if (!root) {
        return;
    }
    root->height = 1 + max(Height(root->left), Height(root->right));
    int balance = GetBalance(root);
    
    if (balance > 1 && GetBalance(root->left) >= 0) {
        RightRotate(root);
    }
    else if (balance > 1 && GetBalance(root->left) < 0) {
        LeftRotate(root->left);
        RightRotate(root);
    }
    else if (balance < -1 && GetBalance(root->right) <= 0) {
        LeftRotate(root);
    }
    else if (balance < -1 && GetBalance(root->right) > 0) {
        RightRotate(root->right);
        LeftRotate(root);
    }
}

NODE* Search(NODE* root, int key) {
    if (!root || root->key == key) {
        return root;
    }
    else if (key < root->key) {
        return Search(root->left, key);
    }
    else if (key > root->key) {
        return Search(root->right, key);
    }
}

void InorderTraversal(NODE* root) {
    if (root->left) {
        InorderTraversal(root->left);
    }
    cout << "key: " << root->key << endl;
    if (root->right) {
        InorderTraversal(root->right);
    }
}

int main() {
    NODE* root = nullptr;
    Insert(root, 100);
    Insert(root, 120);
    Insert(root, 50);
    Insert(root, 30);
    Insert(root, 65);
    Insert(root, 20);
    InorderTraversal(root);
    cout << endl;
    Remove(root, 50);
    InorderTraversal(root);
    DeleteTree(root);
    root = nullptr;
    return 0;
}