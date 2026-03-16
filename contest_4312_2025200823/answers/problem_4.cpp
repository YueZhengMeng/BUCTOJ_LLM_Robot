/* Bracket Matching using Linked-List Stack */
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

typedef Node* Stack;

// Initialize stack (set to empty)
void InitStack(Stack &S) {
    S = nullptr;
}

// Destroy stack and free all nodes
void DestroyStack(Stack &S) {
    while (S != nullptr) {
        Node* temp = S;
        S = S->next;
        delete temp;
    }
}

// Push a character onto the stack
void Push(Stack &S, char data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = S;
    S = newNode;
}

// Check if stack is empty
bool IsEmpty(const Stack &S) {
    return S == nullptr;
}

// Pop top element from stack
char Pop(Stack &S) {
    if (IsEmpty(S)) {
        return '\0';
    }
    char topData = S->data;
    Node* temp = S;
    S = S->next;
    delete temp;
    return topData;
}

// Check if parentheses in the string are matched
bool isMatching(const string &str) {
    Stack S;
    InitStack(S);
    
    for (char c : str) {
        if (c == '(') {
            Push(S, c);
        }
        else if (c == ')') {
            if (IsEmpty(S)) {
                DestroyStack(S);
                return false; // Unmatched closing bracket
            }
            Pop(S); // Match found, remove corresponding '('
        }
    }
    
    bool result = IsEmpty(S); // True if all '(' were matched
    DestroyStack(S);
    return result;
}

// Process each line of input
void BracketMatch() {
    string line;
    while (getline(cin, line)) {
        if (isMatching(line)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    BracketMatch();
    return 0;
}