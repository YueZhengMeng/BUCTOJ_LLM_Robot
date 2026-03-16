/* 
   Decimal to Octal Conversion using a Linked-Stack
   Key techniques:
   1. Repeated division by 8, pushing remainders onto a stack.
   2. Stack reversal gives correct digit order.
   3. Special case for 0.
*/
#include <iostream>
#include <cstdio>
using namespace std;

struct Node {
    int data;
    Node* next;
};
typedef Node* Stack;

// Initialize stack to empty
void InitStack(Stack& S) {
    S = nullptr;
}

// Destroy stack and free all nodes
void DestroyStack(Stack& S) {
    while (S != nullptr) {
        Node* temp = S;
        S = S->next;
        delete temp;
    }
}

// Push an element onto the stack. Returns 0 on success.
int Push(Stack& S, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = S;
    S = newNode;
    return 0;
}

// Check if stack is empty: 1 if empty, 0 otherwise
int IsEmpty(const Stack& S) {
    if (S == nullptr)
        return 1;
    else
        return 0;
}

// Get top element of stack. Returns -1 and prints error if empty.
int Top(Stack& S) {
    if (IsEmpty(S)) {
        cout << "error, Top an empty stack" << endl;
        return -1;
    }
    return S->data;
}

// Pop top element from stack. Returns popped value or -1 if empty.
int Pop(Stack& S) {
    if (IsEmpty(S)) {
        cout << "error, Pop an empty stack" << endl;
        return -1;
    }
    int val = S->data;
    Node* temp = S;
    S = S->next;
    delete temp;
    return val;
}

// (Provided) Print stack for debugging
void PrintStack(const Stack& S) {
    cout << "======test code=====" << endl;
    Node* p = S;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    cout << "======test code=====" << endl;
}

// Convert decimal number to octal and print
void Conversion(int num) {
    if (num == 0) {
        cout << 0 << endl;
        return;
    }
    Stack stk;
    InitStack(stk);
    // Push remainders onto stack
    while (num > 0) {
        int remainder = num % 8;
        Push(stk, remainder);
        num /= 8;
    }
    // Pop and print digits
    while (!IsEmpty(stk)) {
        int digit = Pop(stk);
        cout << digit;
    }
    cout << endl;
    // Free stack memory
    DestroyStack(stk);
}

int main() {
    // freopen("/config/workspace/answer/DataStructure/test.in", "r", stdin);
    int num;
    while (cin >> num) {
        Conversion(num);
    }
    return 0;
}