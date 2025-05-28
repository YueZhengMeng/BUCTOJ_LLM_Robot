#include <iostream>
#include <cmath> // For std::sqrt

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n;
    std::cin >> n;

    // The formula for minimum stamps is 2*N + ceil(sqrt(4*N))
    // Let Y = 4*N. We need to calculate C = ceil(sqrt(Y)).
    long long Y = 4LL * n;
    
    // Calculate k = floor(sqrt(Y))
    // std::sqrt returns a double, static_cast<long long> truncates (acts as floor for positive numbers)
    long long k = static_cast<long long>(std::sqrt(static_cast<double>(Y)));
    
    long long C_sqrt_Y; // This will be ceil(sqrt(Y))
    
    // Check if Y is a perfect square k*k.
    // If k*k == Y, then sqrt(Y) is k, so ceil(sqrt(Y)) is k.
    // Otherwise, k is floor(sqrt(Y)), so ceil(sqrt(Y)) is k+1.
    if (k * k == Y) {
        C_sqrt_Y = k;
    } else {
        // If k*k < Y, then k is floor(sqrt(Y)) and sqrt(Y) is not an integer.
        // So ceil(sqrt(Y)) = k + 1.
        // We also need to consider if k was slightly underestimated due to precision
        // e.g. Y=8.99999..., sqrt(Y) approx 2.999..., k=2. (k+1)^2 = 9 > Y. C=k+1.
        // e.g. Y=9.00000..., sqrt(Y) approx 3.000..., k=3. k*k=Y. C=k.
        // A robust way: if k*k < Y, then ceil is k+1. Else (k*k >= Y implies k*k==Y as k=floor(sqrt(Y))), ceil is k.
        // The initial logic `if (k * k == Y)` handles perfect squares.
        // For non-perfect squares, `k` is `floor(sqrt(Y))`, so `ceil(sqrt(Y))` is `k+1`.
        C_sqrt_Y = k + 1;
    }
    
    long long result = 2LL * n + C_sqrt_Y;
    std::cout << result << std::endl;
    
    return 0;
}