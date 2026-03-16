/* Problem K: Check if nth Fibonacci number is divisible by 3
   Algorithm: Iterative Fibonacci generation + modulo check */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Base Fibonacci numbers (1-indexed)
    int fib_prev_prev = 1;  // F₁
    int fib_prev = 1;       // F₂
    int fib_curr = 1;       // Initialize for n ≤ 2
    
    // Iteratively compute Fibonacci numbers
    for (int i = 3; i <= n; i++) {
        fib_curr = fib_prev + fib_prev_prev;
        fib_prev_prev = fib_prev;
        fib_prev = fib_curr;
    }
    
    // Output Y if divisible by 3, otherwise N
    if (fib_curr % 3 == 0) {
        cout << "Y" << endl;
    } else {
        cout << "N" << endl;
    }
    
    return 0;
}