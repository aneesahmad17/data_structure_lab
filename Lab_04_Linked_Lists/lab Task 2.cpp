// Lab Task 2: Hospital Patient Queue (Singly Linked List)
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string patientID;
    Node* next;
};

class PatientQueue {
    Node* head;
public:
    PatientQueue() { head = nullptr; }

    // Add a new patient at the end of the list
    void addPatient(string id) {
        Node* newNode = new Node;
        newNode->patientID = id;
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

    // Display all waiting patients
    void display(string title) {
        cout << title << endl;
        if (head == nullptr) {
            cout << "No patients waiting." << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->patientID;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Remove the first patient (doctor attends them)
    void servePatient() {
        if (head == nullptr) {
            cout << "No patients to serve." << endl;
            return;
        }
        Node* temp = head;
        cout << "Patient " << temp->patientID << " is being served." << endl;
        head = head->next;
        delete temp;
    }

    ~PatientQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    PatientQueue queue;
    int choice;
    string id;

    do {
        cout << "\n===== Hospital Patient Queue =====" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Display Waiting Patients" << endl;
        cout << "3. Serve Next Patient" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Patient ID (e.g. P101): ";
            cin >> id;
            queue.addPatient(id);
            cout << "Patient " << id << " added to queue." << endl;
            break;
        case 2:
            queue.display("Waiting Patients:");
            break;
        case 3:
            queue.servePatient();
            cout << endl;
            queue.display("Updated Queue:");
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