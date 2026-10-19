#include <iostream>
#include <string>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;
    Node(int k) {
        key = k;
        height = 1;
        left = right = NULL;
    }
};

string caseFound = "";   // stores which rotation case occurred

int height(Node* n) { return n ? n->height : 0; }

int balance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

void update(Node* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

void display(Node* root, int space = 0) {
    if (!root) return;
    space += 8;
    display(root->right, space);
    cout << endl;
    for (int i = 8; i < space; i++) cout << " ";
    cout << root->key << "(" << balance(root) << ")" << endl;
    display(root->left, space);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    update(root);
    int bf = balance(root);

    if (bf > 1 && key < root->left->key) {
        caseFound = "LL";
        cout << "\nImbalance at node " << root->key << ": BF = " << bf
             << ", left child BF = " << balance(root->left) << " => LL Case\n";
        cout << "\nTree BEFORE rotation (node(balance factor)):\n";
        display(root);
        root = rotateRight(root);
        cout << "\nAfter Right Rotation:\n";
        return root;
    }
    if (bf < -1 && key > root->right->key) {
        caseFound = "RR";
        cout << "\nImbalance at node " << root->key << ": BF = " << bf
             << ", right child BF = " << balance(root->right) << " => RR Case\n";
        cout << "\nTree BEFORE rotation (node(balance factor)):\n";
        display(root);
        root = rotateLeft(root);
        cout << "\nAfter Left Rotation:\n";
        return root;
    }
    if (bf > 1 && key > root->left->key) {
        caseFound = "LR";
        cout << "\nImbalance at node " << root->key << ": BF = " << bf
             << ", left child BF = " << balance(root->left) << " => LR Case\n";
        cout << "\nTree BEFORE rotation (node(balance factor)):\n";
        display(root);
        root->left = rotateLeft(root->left);
        cout << "\nAfter Left Rotation on " << root->left->key << ":\n";
        display(root);
        root = rotateRight(root);
        cout << "\nAfter Right Rotation on " << root->right->key << ":\n";
        return root;
    }
    if (bf < -1 && key < root->right->key) {
        caseFound = "RL";
        cout << "\nImbalance at node " << root->key << ": BF = " << bf
             << ", right child BF = " << balance(root->right) << " => RL Case\n";
        cout << "\nTree BEFORE rotation (node(balance factor)):\n";
        display(root);
        root->right = rotateRight(root->right);
        cout << "\nAfter Right Rotation on " << root->right->key << ":\n";
        display(root);
        root = rotateLeft(root);
        cout << "\nAfter Left Rotation on " << root->left->key << ":\n";
        return root;
    }
    return root;
}

void demo(int a, int b, int c, string name) {
    Node* root = NULL;
    int seq[3] = {a, b, c};
    cout << "\n===== " << name << " Rotation Demo =====\n";
    cout << "Insertion sequence: " << a << ", " << b << ", " << c << endl;
    for (int i = 0; i < 3; i++) {
        cout << "\nInserting " << seq[i] << "...\n";
        root = insert(root, seq[i]);
        if (i < 2) display(root);
    }
    cout << "\nFinal balanced tree (node(balance factor)):\n";
    display(root);
}

int main() {
    int choice;
    do {
        cout << "\n===== AVL ROTATION DEMONSTRATION =====\n";
        cout << "1. LL Rotation (30, 20, 10)\n";
        cout << "2. RR Rotation (10, 20, 30)\n";
        cout << "3. LR Rotation (30, 10, 20)\n";
        cout << "4. RL Rotation (10, 30, 20)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: demo(30, 20, 10, "LL"); break;
            case 2: demo(10, 20, 30, "RR"); break;
            case 3: demo(30, 10, 20, "LR"); break;
            case 4: demo(10, 30, 20, "RL"); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}
