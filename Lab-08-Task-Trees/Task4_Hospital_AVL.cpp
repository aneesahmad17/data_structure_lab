// Lab 08 - Task 4: Hospital Appointment System (AVL Tree)
// Name: Anees Ahmad   Roll No: 2502491   BSDS (III Evening)

#include <iostream>
#include <string>
using namespace std;

// Node class: stores one appointment token number
class Node {
public:
    int token;
    Node* left;
    Node* right;
    int height;

    Node(int t) {
        token = t;
        left = NULL;
        right = NULL;
        height = 1;          // a new node is a leaf, height = 1
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = NULL;
    }

    int height(Node* n) {
        if (n == NULL)
            return 0;
        return n->height;
    }

    int maxOf(int a, int b) {
        return (a > b) ? a : b;
    }

    void updateHeight(Node* n) {
        n->height = 1 + maxOf(height(n->left), height(n->right));
    }

    // Balance Factor = height(left) - height(right)
    int balanceFactor(Node* n) {
        if (n == NULL)
            return 0;
        return height(n->left) - height(n->right);
    }

    // Right Rotation (used for LL case)
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;            // x is the new root of this subtree
    }

    // Left Rotation (used for RR case)
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;            // y is the new root of this subtree
    }

    // Insert using BST rules, then balance
    Node* insert(Node* node, int token) {
        // 1) Normal BST insertion
        if (node == NULL)
            return new Node(token);

        if (token < node->token)
            node->left = insert(node->left, token);
        else if (token > node->token)
            node->right = insert(node->right, token);
        else
            return node;     // duplicate tokens are not allowed

        // 2) Update height of this node
        updateHeight(node);

        // 3) Check balance factor
        int bf = balanceFactor(node);

        // LL Case
        if (bf > 1 && token < node->left->token) {
            cout << "   Unbalanced at " << node->token << " (BF = " << bf << ")"
                 << " -> LL Case -> Right Rotation" << endl;
            return rightRotate(node);
        }

        // RR Case
        if (bf < -1 && token > node->right->token) {
            cout << "   Unbalanced at " << node->token << " (BF = " << bf << ")"
                 << " -> RR Case -> Left Rotation" << endl;
            return leftRotate(node);
        }

        // LR Case
        if (bf > 1 && token > node->left->token) {
            cout << "   Unbalanced at " << node->token << " (BF = " << bf << ")"
                 << " -> LR Case -> Left Rotation then Right Rotation" << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (bf < -1 && token < node->right->token) {
            cout << "   Unbalanced at " << node->token << " (BF = " << bf << ")"
                 << " -> RL Case -> Right Rotation then Left Rotation" << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;         // already balanced
    }

    void insert(int token) {
        cout << "Inserting token " << token << endl;
        root = insert(root, token);
    }

    // In-order traversal: gives tokens in sorted order
    void inOrder(Node* node) {
        if (node == NULL)
            return;
        inOrder(node->left);
        cout << node->token << " ";
        inOrder(node->right);
    }

    // Show height and balance factor of every node (in-order)
    void showDetails(Node* node) {
        if (node == NULL)
            return;
        showDetails(node->left);
        cout << "   Token " << node->token
             << "  ->  Height = " << node->height
             << ",  Balance Factor = " << balanceFactor(node) << endl;
        showDetails(node->right);
    }

    // Print the tree sideways (root on the left, right child on top)
    void printTree(Node* node, int space) {
        if (node == NULL)
            return;
        space += 8;
        printTree(node->right, space);
        for (int i = 8; i < space; i++)
            cout << " ";
        cout << node->token << endl;
        printTree(node->left, space);
    }

    // Print each node with its children
    void showStructure(Node* node) {
        if (node == NULL)
            return;
        cout << "   " << node->token << " : Left = ";
        if (node->left) cout << node->left->token; else cout << "NULL";
        cout << ", Right = ";
        if (node->right) cout << node->right->token; else cout << "NULL";
        cout << endl;
        showStructure(node->left);
        showStructure(node->right);
    }
};

int main() {
    cout << "===== Hospital Appointment System (AVL Tree) =====" << endl << endl;

    AVLTree hospital;
    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int i = 0; i < 7; i++)
        hospital.insert(tokens[i]);

    cout << endl << "In-order Traversal (sorted tokens):" << endl << "   ";
    hospital.inOrder(hospital.root);
    cout << endl;

    cout << endl << "Height and Balance Factor of each node:" << endl;
    hospital.showDetails(hospital.root);

    cout << endl << "Root of the balanced tree: " << hospital.root->token << endl;

    cout << endl << "Final Balanced Tree (parent -> children):" << endl;
    hospital.showStructure(hospital.root);

    cout << endl << "Final Balanced Tree (diagram):" << endl << endl;
    cout << "                45" << endl;
    cout << "             /      \\" << endl;
    cout << "           25        65" << endl;
    cout << "          /  \\      /  \\" << endl;
    cout << "        15    35  55    75" << endl;

    cout << endl << "Final Balanced Tree (printed by program, rotated 90 degrees):" << endl;
    hospital.printTree(hospital.root, 0);

    // Extra check: the other rotation cases also work
    cout << endl << "===== Testing LL, LR and RL cases =====" << endl;

    cout << endl << "LL test (30, 20, 10):" << endl;
    AVLTree t1;
    t1.insert(30); t1.insert(20); t1.insert(10);
    cout << "   Root after balancing = " << t1.root->token << endl;

    cout << endl << "LR test (30, 10, 20):" << endl;
    AVLTree t2;
    t2.insert(30); t2.insert(10); t2.insert(20);
    cout << "   Root after balancing = " << t2.root->token << endl;

    cout << endl << "RL test (10, 30, 20):" << endl;
    AVLTree t3;
    t3.insert(10); t3.insert(30); t3.insert(20);
    cout << "   Root after balancing = " << t3.root->token << endl;

    return 0;
}
