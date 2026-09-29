// Lab Task 1: Student Registration System (Singly Linked List)
#include <iostream>
using namespace std;

struct Node {
    int rollNo;
    Node* next;
};

class StudentList {
    Node* head;
public:
    StudentList() { head = nullptr; }

    // Add a new student at the end of the list
    void addStudent(int roll) {
        Node* newNode = new Node;
        newNode->rollNo = roll;
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

    // Display all registered students
    void display() {
        if (head == nullptr) {
            cout << "No students registered." << endl;
            return;
        }
        cout << "Registered Students:" << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->rollNo;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Search for a student by roll number
    bool search(int roll) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->rollNo == roll) return true;
            temp = temp->next;
        }
        return false;
    }

    ~StudentList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    StudentList list;
    int choice, roll;

    do {
        cout << "\n===== Student Registration System =====" << endl;
        cout << "1. Register Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Roll Number: ";
            cin >> roll;
            list.addStudent(roll);
            cout << "Student " << roll << " registered." << endl;
            break;
        case 2:
            list.display();
            break;
        case 3:
            cout << "Enter Roll Number to Search: ";
            cin >> roll;
            if (list.search(roll))
                cout << "Student Found" << endl;
            else
                cout << "Student Not Found" << endl;
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
