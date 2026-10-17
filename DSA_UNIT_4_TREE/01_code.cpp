
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    int height;
    Node *left, *right;

    Node(int value)
    {
        data = value;
        height = 1;
        left = right = NULL;
    }
};

int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(Node *node)
{
    if (node == NULL)
        return 0;

    return getHeight(node->left) -
           getHeight(node->right);
}

void updateHeight(Node *node)
{
    node->height = 1 + max(getHeight(node->left),
                           getHeight(node->right));
}

// Display the tree sideways
void displayTree(Node *root, int space = 0)
{
    if (root == NULL)
        return;

    space += 5;

    displayTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->data << endl;

    displayTree(root->left, space);
}

// Right rotation: LL case
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left rotation: RR case
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *insert(Node *root, int key)
{
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root;

    updateHeight(root);

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 &&
        key < root->left->data)
    {
        cout << "\nBefore LL rotation:\n";
        displayTree(root);

        root = rightRotate(root);

        cout << "\nAfter LL rotation:\n";
        displayTree(root);
    }

    // RR Case
    else if (balance < -1 &&
             key > root->right->data)
    {
        cout << "\nBefore RR rotation:\n";
        displayTree(root);

        root = leftRotate(root);

        cout << "\nAfter RR rotation:\n";
        displayTree(root);
    }

    // LR Case
    else if (balance > 1 &&
             key > root->left->data)
    {
        cout << "\nBefore first rotation (LR):\n";
        displayTree(root);

        root->left = leftRotate(root->left);

        cout << "\nAfter first (left) rotation:\n";
        displayTree(root);

        cout << "\nBefore second (right) rotation:\n";
        displayTree(root);

        root = rightRotate(root);

        cout << "\nAfter LR rotation:\n";
        displayTree(root);
    }

    // RL Case
    else if (balance < -1 &&
             key < root->right->data)
    {
        cout << "\nBefore first rotation (RL):\n";
        displayTree(root);

        root->right = rightRotate(root->right);

        cout << "\nAfter first (right) rotation:\n";
        displayTree(root);

        cout << "\nBefore second (left) rotation:\n";
        displayTree(root);

        root = leftRotate(root);

        cout << "\nAfter RL rotation:\n";
        displayTree(root);
    }

    return root;
}

void demonstrateRotation(const char *name,
                         int values[], int n)
{
    Node *root = NULL;

    cout << "\n================================\n";
    cout << name << " ROTATION DEMONSTRATION\n";
    cout << "Insertion sequence: ";

    for (int i = 0; i < n; i++)
        cout << values[i] << " ";

    cout << "\n================================\n";

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    cout << "\nFinal balanced tree:\n";
    displayTree(root);
    cout << "\n";
}

int main()
{
    int ll[] = {30, 20, 10};
    int rr[] = {10, 20, 30};
    int lr[] = {30, 10, 20};
    int rl[] = {10, 30, 20};

    demonstrateRotation("LL", ll, 3);
    demonstrateRotation("RR", rr, 3);
    demonstrateRotation("LR", lr, 3);
    demonstrateRotation("RL", rl, 3);

    return 0;
}


