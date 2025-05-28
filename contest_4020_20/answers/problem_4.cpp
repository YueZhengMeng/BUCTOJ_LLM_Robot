#include <iostream>
#include <vector>

// Max N = 10^6, K = 1000.
// Estimated max current_pos ~ 1.3 * 10^6.
// The prime p found will be > current_pos, so p can be ~1.3*10^6 + (max_gap ~150).
// Sieve up to 1.5 * 10^6 should be safe.
const int SIEVE_LIMIT = 1500005; 
std::vector<bool> is_prime_sieve(SIEVE_LIMIT + 1, true);

void sieve() {
    if (SIEVE_LIMIT >= 0) is_prime_sieve[0] = false; // 0 is not prime
    if (SIEVE_LIMIT >= 1) is_prime_sieve[1] = false; // 1 is not prime

    for (int p = 2; p * p <= SIEVE_LIMIT; ++p) {
        if (is_prime_sieve[p]) {
            for (int i = p * p; i <= SIEVE_LIMIT; i += p)
                is_prime_sieve[i] = false;
        }
    }
}

long long find_next_prime(long long current_x) {
    // current_x can be up to ~1.3 * 10^6 based on analysis.
    // So current_x + 1 will be within SIEVE_LIMIT.
    for (long long cand = current_x + 1; cand <= SIEVE_LIMIT; ++cand) {
        if (is_prime_sieve[cand]) {
            return cand;
        }
    }
    // This part should not be reached if SIEVE_LIMIT is chosen correctly
    // and analysis of max position is correct.
    return -1; // Should indicate an error or insufficient SIEVE_LIMIT
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    sieve(); // Precompute primes

    long long N_start;
    int K_jumps;
    std::cin >> N_start >> K_jumps;

    long long current_pos = N_start;
    const long long MOD = 1e9 + 7;

    for (int i = 0; i < K_jumps; ++i) {
        long long p_val = find_next_prime(current_pos);
        
        // In a contest, one would rely on analysis that p_val is always found.
        // If p_val could be -1, error handling would be needed.
        
        current_pos = 2 * p_val - current_pos;
    }

    std::cout << current_pos % MOD << std::endl;

    return 0;
}