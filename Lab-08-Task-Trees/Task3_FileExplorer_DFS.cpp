// Lab 08 - Task 3: Computer File Explorer (DFS Traversal)
// Name: Anees Ahmad   Roll No: 2502491   BSDS (III Evening)

#include <iostream>
#include <string>
using namespace std;

// Node class: stores one folder name
class Node {
public:
    string folder;
    Node* left;
    Node* right;

    Node(string f) {
        folder = f;
        left = NULL;
        right = NULL;
    }
};

// In-order: Left -> Root -> Right
void inOrder(Node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    cout << root->folder << "  ";
    inOrder(root->right);
}

// Pre-order: Root -> Left -> Right
void preOrder(Node* root) {
    if (root == NULL)
        return;
    cout << root->folder << "  ";
    preOrder(root->left);
    preOrder(root->right);
}

// Post-order: Left -> Right -> Root
void postOrder(Node* root) {
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->folder << "  ";
}

int main() {
    // Create folder nodes
    Node* root       = new Node("C:");
    Node* documents  = new Node("Documents");
    Node* downloads  = new Node("Downloads");
    Node* university = new Node("University");
    Node* personal   = new Node("Personal");
    Node* software   = new Node("Software");
    Node* movies     = new Node("Movies");

    // Connect folders and subfolders
    root->left = documents;
    root->right = downloads;

    documents->left = university;
    documents->right = personal;

    downloads->left = software;
    downloads->right = movies;

    cout << "===== Computer File Explorer =====" << endl << endl;
    cout << "                   C:" << endl;
    cout << "              /          \\" << endl;
    cout << "        Documents       Downloads" << endl;
    cout << "         /     \\          /     \\" << endl;
    cout << " University  Personal  Software  Movies" << endl << endl;

    cout << "1) Pre-order  (Root -> Left -> Right):" << endl << "   ";
    preOrder(root);
    cout << endl << endl;

    cout << "2) In-order   (Left -> Root -> Right):" << endl << "   ";
    inOrder(root);
    cout << endl << endl;

    cout << "3) Post-order (Left -> Right -> Root):" << endl << "   ";
    postOrder(root);
    cout << endl << endl;

    cout << "Visiting order:" << endl;
    cout << " - Pre-order visits the parent folder FIRST, then its subfolders." << endl;
    cout << " - In-order visits the left subfolder, then the parent, then the right subfolder." << endl;
    cout << " - Post-order visits all subfolders FIRST and the parent folder LAST." << endl;

    return 0;
}
