// Lab 08 - Task 2: Hospital and Emergency Inventory Management System
// Menu-driven Binary Search Tree application
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;
    Node(int v) : id(v), left(NULL), right(NULL) {}
};

class BST {
private:
    Node* root;

    void destroy(Node* node) {
        if (node == NULL) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
    void inorder(Node* node) {
        if (node == NULL) return;
        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }
    void preorder(Node* node) {
        if (node == NULL) return;
        cout << node->id << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void postorder(Node* node) {
        if (node == NULL) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->id << " ";
    }
    int count(Node* node) {
        if (node == NULL) return 0;
        return 1 + count(node->left) + count(node->right);
    }
    int height(Node* node) {            // edges on longest root-to-leaf path
        if (node == NULL) return -1;
        int l = height(node->left), r = height(node->right);
        return 1 + (l > r ? l : r);
    }
    Node* findMin(Node* node) {
        while (node->left != NULL) node = node->left;
        return node;
    }
    Node* removeNode(Node* node, int id, string& kind) {
        if (node == NULL) return NULL;
        if (id < node->id)      node->left  = removeNode(node->left, id, kind);
        else if (id > node->id) node->right = removeNode(node->right, id, kind);
        else {
            if (node->left == NULL && node->right == NULL) {          // leaf
                if (kind.empty()) kind = "leaf node";
                delete node;
                return NULL;
            }
            if (node->left == NULL || node->right == NULL) {          // one child
                if (kind.empty()) kind = "node with one child";
                Node* child = (node->left != NULL) ? node->left : node->right;
                delete node;
                return child;
            }
            // two children: copy in-order successor, then delete successor
            kind = "node with two children";
            Node* succ = findMin(node->right);
            cout << "  In-order successor " << succ->id
                 << " replaces " << node->id << ".\n";
            node->id = succ->id;
            string ignore = "x";
            node->right = removeNode(node->right, succ->id, ignore);
        }
        return node;
    }

public:
    BST() : root(NULL) {}
    ~BST() {
        destroy(root);
        cout << "Destructor: all dynamically allocated nodes released.\n";
    }

    bool isEmpty() { return root == NULL; }

    bool insert(int id) {
        Node** cur = &root;
        while (*cur != NULL) {
            if (id == (*cur)->id) return false;       // duplicate
            cur = (id < (*cur)->id) ? &(*cur)->left : &(*cur)->right;
        }
        *cur = new Node(id);
        return true;
    }

    bool search(int id, int& visits) {
        visits = 0;
        Node* cur = root;
        while (cur != NULL) {
            visits++;
            if (cur->id == id) return true;
            cur = (id < cur->id) ? cur->left : cur->right;
        }
        return false;
    }

    bool remove(int id, string& kind) {
        int v;
        if (!search(id, v)) return false;
        kind = "";
        root = removeNode(root, id, kind);
        return true;
    }

    void displayInorder()   { inorder(root);   cout << endl; }
    void displayPreorder()  { preorder(root);  cout << endl; }
    void displayPostorder() { postorder(root); cout << endl; }
    int countNodes() { return count(root); }
    int getHeight()  { return height(root); }
};

int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input! Please enter a number.\n";
    }
}

void showMenu() {
    cout << "\n========== HOSPITAL INVENTORY BST MENU ==========\n"
         << " 1. Insert an ID            6. Post-order traversal\n"
         << " 2. Search for an ID        7. Count total nodes\n"
         << " 3. Delete an ID            8. Height of the BST\n"
         << " 4. In-order traversal      9. Exit\n"
         << " 5. Pre-order traversal\n"
         << "=================================================\n";
}

int main() {
    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int i = 0; i < 9; i++) tree.insert(initial[i]);
    cout << "Initial IDs inserted: 55 35 75 25 45 65 85 40 50\n";

    int choice;
    do {
        showMenu();
        choice = readInt("Enter your choice (1-9): ");
        if (choice < 1 || choice > 9) {
            cout << "  Invalid choice! Please select 1 to 9.\n";
            continue;
        }
        int id, visits;
        string kind;
        switch (choice) {
        case 1:
            id = readInt("Enter ID to insert: ");
            if (tree.insert(id)) cout << "  ID " << id << " inserted successfully.\n";
            else cout << "  Duplicate ID " << id << " rejected. Tree not modified.\n";
            break;
        case 2:
            if (tree.isEmpty()) { cout << "  Tree is empty. Nothing to search.\n"; break; }
            id = readInt("Enter ID to search: ");
            if (tree.search(id, visits))
                cout << "  ID " << id << " FOUND (nodes visited: " << visits << ").\n";
            else
                cout << "  ID " << id << " does NOT exist (nodes visited: " << visits << ").\n";
            break;
        case 3:
            if (tree.isEmpty()) { cout << "  Tree is empty. Nothing to delete.\n"; break; }
            id = readInt("Enter ID to delete: ");
            if (tree.remove(id, kind)) {
                cout << "  ID " << id << " deleted (" << kind << ").\n";
                cout << "  Updated IDs (in-order): ";
                if (tree.isEmpty()) cout << "(tree is now empty)\n";
                else tree.displayInorder();
            } else {
                cout << "  ID " << id << " does not exist. Nothing deleted.\n";
            }
            break;
        case 4:
            if (tree.isEmpty()) { cout << "  Tree is empty.\n"; break; }
            cout << "  In-order   : "; tree.displayInorder(); break;
        case 5:
            if (tree.isEmpty()) { cout << "  Tree is empty.\n"; break; }
            cout << "  Pre-order  : "; tree.displayPreorder(); break;
        case 6:
            if (tree.isEmpty()) { cout << "  Tree is empty.\n"; break; }
            cout << "  Post-order : "; tree.displayPostorder(); break;
        case 7:
            cout << "  Total number of nodes: " << tree.countNodes() << endl; break;
        case 8:
            if (tree.isEmpty()) cout << "  Tree is empty (height = -1).\n";
            else cout << "  Height of BST (edges on longest path): " << tree.getHeight() << endl;
            break;
        case 9:
            cout << "  Exiting program. Goodbye!\n"; break;
        }
    } while (choice != 9);
    return 0;
}
