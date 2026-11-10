// Lab 08 - Task 1: University Department Hierarchy (Binary Tree Creation)
// Name: Anees Ahmad   Roll No: 2502491   BSDS (III Evening)

#include <iostream>
#include <string>
using namespace std;

// Node class: stores one department member
class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

// Show a child's name, or "NULL" if there is no child
string childName(Node* child) {
    if (child == NULL)
        return "NULL";
    return child->name;
}

// Display each member with its left and right child (pre-order)
void displayMembers(Node* root) {
    if (root == NULL)
        return;

    cout << "Member: " << root->name << endl;
    cout << "   Left Child : " << childName(root->left) << endl;
    cout << "   Right Child: " << childName(root->right) << endl;
    cout << "----------------------------------------------" << endl;

    displayMembers(root->left);
    displayMembers(root->right);
}

int main() {
    // Create nodes (7 department members)
    Node* hod   = new Node("Dr. Ahmed (HOD)");
    Node* coord1 = new Node("Dr. Sara (Coordinator BSDS)");
    Node* coord2 = new Node("Dr. Usman (Coordinator MS)");
    Node* fac1  = new Node("Mr. Ali (Faculty)");
    Node* fac2  = new Node("Ms. Hina (Faculty)");
    Node* fac3  = new Node("Mr. Bilal (Faculty)");
    Node* fac4  = new Node("Ms. Ayesha (Faculty)");

    // Connect parent and child nodes
    hod->left = coord1;
    hod->right = coord2;

    coord1->left = fac1;
    coord1->right = fac2;

    coord2->left = fac3;
    coord2->right = fac4;

    cout << "===== University Department Hierarchy =====" << endl << endl;
    cout << "                 Dr. Ahmed (HOD)" << endl;
    cout << "                /               \\" << endl;
    cout << "       Dr. Sara (BSDS)        Dr. Usman (MS)" << endl;
    cout << "        /       \\              /        \\" << endl;
    cout << "   Mr. Ali   Ms. Hina     Mr. Bilal   Ms. Ayesha" << endl << endl;

    cout << "----------------------------------------------" << endl;
    displayMembers(hod);

    return 0;
}
