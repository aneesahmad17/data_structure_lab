// Lab 08 - Task 2: Online Shopping Categories (BFS Traversal)
// Name: Anees Ahmad   Roll No: 2502491   BSDS (III Evening)

#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Node class: stores one product category
class Node {
public:
    string category;
    Node* left;
    Node* right;

    Node(string c) {
        category = c;
        left = NULL;
        right = NULL;
    }
};

// Breadth-First Traversal using a queue (level by level)
void BFS(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int count = q.size();          // number of nodes on this level
        cout << "Level " << level << ": ";

        for (int i = 0; i < count; i++) {
            Node* current = q.front();
            q.pop();
            cout << current->category << "   ";

            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
        }
        cout << endl;
        level++;
    }
}

// Plain BFS order on one line
void BFSOrder(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->category;

        if (current->left != NULL)
            q.push(current->left);
        if (current->right != NULL)
            q.push(current->right);

        if (!q.empty())
            cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Create category nodes
    Node* root        = new Node("All Products");
    Node* electronics = new Node("Electronics");
    Node* clothing    = new Node("Clothing");
    Node* mobiles     = new Node("Mobiles");
    Node* laptops     = new Node("Laptops");
    Node* men         = new Node("Men");
    Node* women       = new Node("Women");
    Node* accessories = new Node("Accessories");

    // Connect the tree
    root->left = electronics;
    root->right = clothing;

    electronics->left = mobiles;
    electronics->right = laptops;

    clothing->left = men;
    clothing->right = women;

    mobiles->left = accessories;

    cout << "===== Online Shopping Categories =====" << endl << endl;
    cout << "                All Products" << endl;
    cout << "              /              \\" << endl;
    cout << "        Electronics        Clothing" << endl;
    cout << "         /      \\          /     \\" << endl;
    cout << "    Mobiles   Laptops    Men    Women" << endl;
    cout << "      /" << endl;
    cout << " Accessories" << endl << endl;

    cout << "BFS Traversal (level by level):" << endl;
    BFS(root);

    cout << endl << "BFS Order:" << endl;
    BFSOrder(root);

    return 0;
}
