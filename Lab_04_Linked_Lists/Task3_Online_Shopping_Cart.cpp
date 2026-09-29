// Lab Task 3: Online Shopping Cart (Singly Linked List)
#include <iostream>
using namespace std;

// ---------- Helper functions (written manually, no library functions) ----------
// Copy one character array into another
void copyText(char dest[], const char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Compare two character arrays, return true if they are equal
bool isEqual(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

struct Node {
    char productID[20];
    Node* next;
};

class ShoppingCart {
    Node* head;
public:
    ShoppingCart() { head = nullptr; }

    // Add a product to the cart (at the end)
    void addProduct(const char id[]) {
        Node* newNode = new Node;
        copyText(newNode->productID, id);
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    // Display all products in the cart
    void display(const char title[]) {
        cout << title << endl;
        if (head == nullptr) {
            cout << "Cart is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->productID;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Remove a product using its Product ID
    bool removeProduct(const char id[]) {
        if (head == nullptr) return false;

        // Product is at the head
        if (isEqual(head->productID, id)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        // Product is somewhere after the head
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr) {
            if (isEqual(curr->productID, id)) {
                prev->next = curr->next;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    ~ShoppingCart() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ShoppingCart cart;
    int choice;
    char id[20];

    do {
        cout << "\n===== Online Shopping Cart =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Display Cart" << endl;
        cout << "3. Remove Product" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Product ID (e.g. P101): ";
            cin >> id;
            cart.addProduct(id);
            cout << "Product " << id << " added to cart." << endl;
            break;
        case 2:
            cart.display("Shopping Cart:");
            break;
        case 3:
            cout << "Remove Product: ";
            cin >> id;
            if (cart.removeProduct(id)) {
                cout << endl;
                cart.display("Updated Cart:");
            } else {
                cout << "Product " << id << " not found in cart." << endl;
            }
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
