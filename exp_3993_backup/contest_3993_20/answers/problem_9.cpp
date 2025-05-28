#include <iostream>
#include <vector>

// Define a 2x2 matrix structure
struct Matrix {
    long long mat[2][2];

    Matrix() {
        mat[0][0] = mat[0][1] = mat[1][0] = mat[1][1] = 0;
    }
};

const int MOD = 10000;
const int PISANO_PERIOD = 15000; // Pisano period for mod 10000

// Function to multiply two 2x2 matrices modulo MOD
Matrix multiply(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C.mat[i][j] = 0; // Initialize element
            for (int k = 0; k < 2; k++) {
                C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % MOD;
            }
        }
    }
    return C;
}

// Function to compute matrix A raised to power p modulo MOD
Matrix matrix_pow(Matrix A, long long p) {
    Matrix res;
    // Initialize res as identity matrix
    res.mat[0][0] = 1;
    res.mat[1][1] = 1;
    // Other elements are 0 by default constructor

    // A.mat[x][y] %= MOD; // Base matrix T has small values, no need for initial mod

    while (p > 0) {
        if (p % 2 == 1) { // If p is odd
            res = multiply(res, A);
        }
        A = multiply(A, A); // Square the base matrix
        p /= 2;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n_orig;
    while (std::cin >> n_orig && n_orig != -1) {
        long long n_idx_in_period = n_orig % PISANO_PERIOD;

        if (n_idx_in_period == 0) {
            // F_0, F_P, F_2P, etc. are all 0 mod P
            std::cout << 0 << std::endl;
        } else if (n_idx_in_period == 1) {
            // F_1, F_{P+1}, etc. are all 1 mod P
            std::cout << 1 << std::endl;
        } else {
            // For n_idx_in_period >= 2, we need F_{n_idx_in_period}
            // This is M^(n_idx_in_period - 1).mat[0][0]
            Matrix T;
            T.mat[0][0] = 1; T.mat[0][1] = 1;
            T.mat[1][0] = 1; T.mat[1][1] = 0;

            long long exponent = n_idx_in_period - 1; // exponent will be >= 1
            Matrix result_matrix = matrix_pow(T, exponent);
            std::cout << result_matrix.mat[0][0] << std::endl;
        }
    }

    return 0;
}