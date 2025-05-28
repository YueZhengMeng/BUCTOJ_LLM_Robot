#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iomanip> // For std::fixed and std::setprecision if needed for debugging logs

// Global variables for the solution
int N_val;
long double max_log_lcm;
std::vector<int> best_final_config;
std::vector<int> primes;

// Sieve of Eratosthenes to generate primes up to limit
void generate_primes_util(int limit) {
    primes.clear();
    std::vector<bool> is_prime_sieve(limit + 1, true);
    if (limit >= 0) is_prime_sieve[0] = false;
    if (limit >= 1) is_prime_sieve[1] = false;
    for (int p = 2; p * p <= limit; ++p) {
        if (is_prime_sieve[p]) {
            for (int i = p * p; i <= limit; i += p)
                is_prime_sieve[i] = false;
        }
    }
    for (int p = 2; p <= limit; ++p) {
        if (is_prime_sieve[p]) {
            primes.push_back(p);
        }
    }
}

// Recursive function to find the solution
void find_solution_recursive(int k_prime_idx, int current_sum, long double current_log_lcm_val, std::vector<int>& current_selection_list) {
    // Consider the current state (current_selection_list + ones) as a candidate solution
    if (current_sum <= N_val) {
        int ones_to_add = N_val - current_sum;
        
        std::vector<int> temp_current_config = current_selection_list;
        for (int i = 0; i < ones_to_add; ++i) {
            temp_current_config.push_back(1);
        }
        std::sort(temp_current_config.begin(), temp_current_config.end());

        bool update_best = false;
        if (best_final_config.empty()) { // First valid solution found
             update_best = true;
        } else if (current_log_lcm_val > max_log_lcm + 1e-12) { // current is strictly better LCM
            update_best = true;
        } else if (std::abs(current_log_lcm_val - max_log_lcm) < 1e-12) { // LCMs are numerically equal
            if (temp_current_config < best_final_config) { // Current is lexicographically smaller
                update_best = true;
            }
        }

        if (update_best) {
            max_log_lcm = current_log_lcm_val;
            best_final_config = temp_current_config;
        }
    }

    // Base case for recursion: if no more primes to consider or current sum too high for more additions
    if (k_prime_idx == primes.size() || current_sum >= N_val) {
        return;
    }

    // Option 1: Skip prime `primes[k_prime_idx]`
    find_solution_recursive(k_prime_idx + 1, current_sum, current_log_lcm_val, current_selection_list);

    // Option 2: Include a power of `p = primes[k_prime_idx]`
    long long p_val = primes[k_prime_idx];
    long long current_power_val = p_val;

    while (true) {
        if (current_sum + current_power_val <= N_val) {
            current_selection_list.push_back(static_cast<int>(current_power_val));
            find_solution_recursive(k_prime_idx + 1, current_sum + static_cast<int>(current_power_val), current_log_lcm_val + std::log(static_cast<long double>(current_power_val)), current_selection_list);
            current_selection_list.pop_back(); // Backtrack
        } else {
            // If current_sum + current_power_val > N_val, adding this power (or higher powers) makes sum too large.
            break;
        }

        // Prepare for next power: current_power_val * p_val
        if (current_power_val > N_val / p_val) { // Check for overflow before multiplication current_power_val * p_val,
                                                // or if next power would exceed N_val making it unusable.
            break; 
        }
        current_power_val *= p_val;
        // The condition current_sum + current_power_val <= N_val in the next iteration's if
        // will handle cases where current_power_val itself becomes too large relative to N_val - current_sum.
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_val;

    generate_primes_util(N_val);

    max_log_lcm = -1.0L; // Initialize to a very small value, indicating no solution found yet
    best_final_config.clear(); // Ensure it's empty initially

    std::vector<int> current_selection_list;
    // The first evaluation inside find_solution_recursive will handle the all-ones case:
    // k_prime_idx=0, current_sum=0, current_log_lcm_val=0.0L, current_selection_list empty
    // This will form N_val ones, log_lcm = 0.0, and set it as the initial best_final_config.
    find_solution_recursive(0, 0, 0.0L, current_selection_list);
    
    // Fallback if N_val is 0 or no solution better than empty is found (though N>=1 guarantees at least {1...1})
    if (best_final_config.empty() && N_val > 0) {
        for(int i = 0; i < N_val; ++i) best_final_config.push_back(1);
        std::sort(best_final_config.begin(), best_final_config.end()); // Should be sorted anyway
    }


    for (size_t i = 0; i < best_final_config.size(); ++i) {
        std::cout << best_final_config[i] << (i == best_final_config.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}