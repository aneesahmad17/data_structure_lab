// Lab 06 - Task 1: Stack using Array (OOP)
#include <iostream>
using namespace std;

class Stack
{
private:
    static const int SIZE = 5; // Maximum capacity
    int arr[SIZE];             // Array to store elements
    int top;                   // Index of TOP element

public:
    // Constructor: stack starts empty
    Stack()
    {
        top = -1;
    }

    // Check whether stack is empty
    bool isEmpty()
    {
        return top == -1;
    }

    // Check whether stack is full
    bool isFull()
    {
        return top == SIZE - 1;
    }

    // PUSH: add element at TOP
    void push(int value)
    {
        if (isFull())
        {
            cout << "Stack Overflow! Cannot push " << value << "." << endl;
            return;
        }
        top++;
        arr[top] = value;
        cout << value << " pushed into stack." << endl;
    }

    // POP: remove element from TOP
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! Nothing to pop." << endl;
            return;
        }
        cout << arr[top] << " popped from stack." << endl;
        top--;
    }

    // PEEK: show TOP element
    void peek()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty!" << endl;
            return;
        }
        cout << "Top element is: " << arr[top] << endl;
    }

    // DISPLAY: show elements from TOP to bottom
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is Empty!" << endl;
            return;
        }
        cout << "Stack elements (top -> bottom): ";
        for (int i = top; i >= 0; i--)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Stack s;

    cout << "--- Check empty at start ---" << endl;
    cout << "isEmpty(): " << (s.isEmpty() ? "true" : "false") << endl;

    cout << "\n--- PUSH 10, 20, 50, 70 ---" << endl;
    s.push(10);
    s.push(20);
    s.push(50);
    s.push(70);
    s.display();

    cout << "\n--- PEEK ---" << endl;
    s.peek();

    cout << "\n--- POP ---" << endl;
    s.pop();
    s.display();

    cout << "\n--- Updated TOP ---" << endl;
    s.peek();
    cout << "isEmpty(): " << (s.isEmpty() ? "true" : "false") << endl;

    cout << "\n--- Overflow test (push 80, 100, 120) ---" << endl;
    s.push(80);
    s.push(100);
    s.push(120); // stack is full here
    s.display();

    cout << "\n--- Underflow test (pop everything, then once more) ---" << endl;
    while (!s.isEmpty())
    {
        s.pop();
    }
    s.pop(); // stack is empty here
    s.peek();

    return 0;
}
