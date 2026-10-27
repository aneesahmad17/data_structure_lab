// Lab 08 - Task 1: University Staff Management System
// General Binary Tree (staff names) + Binary Search Tree (staff IDs)
#include <iostream>
#include <string>
using namespace std;

// ===================== GENERAL BINARY TREE =====================
class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(const string& n) : name(n), left(NULL), right(NULL) {}
};

class StaffTree {
private:
    Node* root;

    void displayNode(Node* node) {
        if (node == NULL) return;
        cout << "  " << node->name
             << "  ->  Left: " << (node->left ? node->left->name : "NULL")
             << ",  Right: " << (node->right ? node->right->name : "NULL") << endl;
        displayNode(node->left);
        displayNode(node->right);
    }
    void destroy(Node* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->name << "  ";
        inorder(node->right);
    }

public:
    StaffTree() : root(NULL) {}
    ~StaffTree() { destroy(root); }

    // Builds a fixed hierarchy of staff members (not ordered by any rule)
    void build() {
        root               = new Node("Dr. Ayesha (Dean)");
        root->left         = new Node("Prof. Bilal");
        root->right        = new Node("Prof. Sana");
        root->left->left   = new Node("Mr. Usman");
        root->left->right  = new Node("Ms. Hina");
        root->right->left  = new Node("Mr. Kamran");
        root->right->right = new Node("Ms. Zara");
        root->left->left->left = new Node("Mr. Imran");
    }
    void display() { displayNode(root); }
    void displayInorder() { inorder(root); cout << endl; }
};

// ===================== BINARY SEARCH TREE =====================
class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int v) : id(v), left(NULL), right(NULL) {}
};

class BST {
private:
    BSTNode* root;

    BSTNode* copyTree(BSTNode* node) {
        if (node == NULL) return NULL;
        BSTNode* n = new BSTNode(node->id);
        n->left = copyTree(node->left);
        n->right = copyTree(node->right);
        return n;
    }
    void destroy(BSTNode* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void inorder(BSTNode* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }
    BSTNode* findMin(BSTNode* node) {
        while (node->left != NULL) node = node->left;
        return node;
    }
    BSTNode* removeNode(BSTNode* node, int id) {
        if (node == NULL) return NULL;
        if (id < node->id)      node->left  = removeNode(node->left, id);
        else if (id > node->id) node->right = removeNode(node->right, id);
        else {
            // Case 1: leaf node
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            // Case 2: only one child
            if (node->left == NULL) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == NULL) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children -> replace with in-order successor
            BSTNode* succ = findMin(node->right);
            node->id = succ->id;
            node->right = removeNode(node->right, succ->id);
        }
        return node;
    }
    BSTNode* findNode(int id) {
        BSTNode* cur = root;
        while (cur != NULL && cur->id != id)
            cur = (id < cur->id) ? cur->left : cur->right;
        return cur;
    }

public:
    BST() : root(NULL) {}
    BST(const BST& other) : root(copyTree(other.root)) {}   // fresh copy
    ~BST() { destroy(root); }

    bool insert(int id) {
        if (root == NULL) { root = new BSTNode(id); return true; }
        BSTNode* cur = root;
        while (true) {
            if (id == cur->id) return false;              // duplicate rejected
            if (id < cur->id) {
                if (cur->left == NULL) { cur->left = new BSTNode(id); return true; }
                cur = cur->left;
            } else {
                if (cur->right == NULL) { cur->right = new BSTNode(id); return true; }
                cur = cur->right;
            }
        }
    }

    // Returns true if found; 'visits' counts every node examined
    bool search(int id, int& visits) {
        visits = 0;
        BSTNode* cur = root;
        while (cur != NULL) {
            visits++;
            if (id == cur->id) return true;
            cur = (id < cur->id) ? cur->left : cur->right;
        }
        return false;
    }

    // Describes which deletion case applies to this ID
    string deletionCase(int id) {
        BSTNode* n = findNode(id);
        if (n == NULL) return "NOT FOUND";
        if (n->left == NULL && n->right == NULL) return "Leaf node";
        if (n->left == NULL || n->right == NULL) return "Node with ONE child";
        return "Node with TWO children";
    }

    bool remove(int id) {
        if (findNode(id) == NULL) return false;
        root = removeNode(root, id);
        return true;
    }

    void displayInorder() {
        if (root == NULL) cout << "(empty)";
        inorder(root);
        cout << endl;
    }
};

// ===================== HELPERS =====================
int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Invalid input. Please enter a whole number.\n";
    }
}

void testSearch(BST& bst, int id, const string& label) {
    int visits;
    bool found = bst.search(id, visits);
    cout << "  [" << label << "] ID " << id << " : "
         << (found ? "FOUND" : "NOT FOUND")
         << "   (nodes visited = " << visits << ")" << endl;
}

int main() {
    cout << "=========================================================\n";
    cout << "     UNIVERSITY STAFF MANAGEMENT SYSTEM (Tree & BST)\n";
    cout << "=========================================================\n\n";

    // ---- Part A: General binary tree ----
    cout << "--- Part A: General Binary Tree of Staff Members ---\n";
    StaffTree staff;
    staff.build();
    staff.display();
    cout << "\n  In-order of general tree: ";
    staff.displayInorder();

    // ---- Part B: BST of staff IDs ----
    cout << "\n--- Part B: Binary Search Tree of Staff IDs ---\n";
    BST bst;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    cout << "  Inserting initial IDs: ";
    for (int i = 0; i < 7; i++) {
        bst.insert(initial[i]);
        cout << initial[i] << " ";
    }
    cout << "\n  In-order: ";
    bst.displayInorder();

    cout << "\n  Enter THREE additional staff IDs:\n";
    int added = 0;
    while (added < 3) {
        int id = readInt("  Enter new staff ID #" + to_string(added + 1) + ": ");
        if (bst.insert(id)) {
            cout << "    -> ID " << id << " registered successfully.\n";
            added++;
        } else {
            cout << "    -> Duplicate ID " << id << " rejected. Tree not modified.\n";
        }
    }
    cout << "  In-order after insertions: ";
    bst.displayInorder();

    // ---- Searching ----
    cout << "\n--- Searching ---\n";
    int key = readInt("  Enter a staff ID to search: ");
    testSearch(bst, key, "User search");
    cout << "\n  Required test cases:\n";
    testSearch(bst, 38, "Existing ID   ");
    testSearch(bst, 50, "Missing ID    ");
    testSearch(bst, 5,  "Smaller than all");

    // ---- Deletion (each test on a fresh copy of the original BST) ----
    cout << "\n--- Deletion (each test uses a FRESH copy of the original BST) ---\n";
    cout << "  Original BST in-order: ";
    bst.displayInorder();
    string tests[] = {"leaf node", "node with one child", "node with two children"};
    for (int t = 0; t < 3; t++) {
        BST copy(bst);   // fresh copy
        cout << "\n  Test " << t + 1 << " (" << tests[t] << ")\n";
        int id = readInt("  Enter staff ID to delete: ");
        string kind = copy.deletionCase(id);
        if (copy.remove(id)) {
            cout << "    Deleted ID " << id << "  [Case: " << kind << "]\n";
            cout << "    Remaining IDs (in-order): ";
            copy.displayInorder();
        } else {
            cout << "    ID " << id << " does not exist. Nothing deleted.\n";
        }
    }

    // ---- Explanation ----
    cout << "\n--- Why is BST in-order sorted but a general tree is not? ---\n";
    cout << "  A general binary tree places nodes anywhere, with no rule linking\n"
         << "  a node's value to its children, so in-order output follows the\n"
         << "  shape of the tree, not the order of values. In a valid BST every\n"
         << "  left-subtree value is smaller and every right-subtree value is\n"
         << "  larger than the node, so Left -> Node -> Right always visits the\n"
         << "  values from smallest to largest (ascending order).\n";
    return 0;
}
