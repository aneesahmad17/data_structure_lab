// Lab 06 - Task 2: Stack using Singly Linked List (OOP)
#include <iostream>
using namespace std;

// One node of the stack
class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = NULL;
    }
};

class Stack
{
private:
    Node* top; // Points to TOP node

public:
    // Constructor: stack starts empty
    Stack()
    {
        top = NULL;
    }

    // Destructor: free all remaining nodes
    ~Stack()
    {
        while (top != NULL)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty()
    {
        return top == NULL;
    }

    // PUSH: insert new node at TOP
    void push(int value)
    {
        Node* newNode = new Node(value);
        newNode->next = top; // new node points to old TOP
        top = newNode;       // new node becomes TOP
        cout << value << " pushed into Stack." << endl;
    }

    // POP: remove TOP node
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << temp->data << " popped from Stack." << endl;
        delete temp;
    }

    // PEEK: show TOP element
    void peek()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty!" << endl;
            return;
        }
        cout << "TOP element: " << top->data << endl;
    }

    // DISPLAY: traverse from TOP to NULL
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty!" << endl;
            return;
        }
        cout << "Stack: ";
        Node* current = top;
        while (current != NULL)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    Stack s;

    // PUSH 11, 22, 33, 44
    s.push(11);
    s.push(22);
    s.push(33);
    s.push(44);

    // Display stack and TOP
    s.display();
    s.peek();

    // POP (removes 44)
    s.pop();

    // Display updated stack and new TOP
    s.display();
    s.peek();

    return 0;
}
