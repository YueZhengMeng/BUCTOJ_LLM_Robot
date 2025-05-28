#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    if (n == 1) {
        int a1;
        std::cin >> a1;
        if (a1 % 2 != 0) {
            std::cout << "Odd\n";
        } else {
            std::cout << "Even\n";
        }
    } else { // n > 1
        // For n > 1, the result is always Even.
        // We must read all n elements to correctly process the input stream,
        // even if their specific values are not used for this case.
        for (int i = 0; i < n; ++i) {
            int temp_val;
            std::cin >> temp_val; // Read and discard
        }
        std::cout << "Even\n";
    }

    return 0;
}