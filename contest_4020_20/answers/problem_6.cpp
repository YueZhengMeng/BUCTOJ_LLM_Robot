#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <tuple> 
#include <climits> 

using namespace std;

typedef long long ll;

int n_global;
ll m_global;
vector<ll> a_global;

map<tuple<int, int, int, bool, bool>, ll> memo;
int M_bits_global[61];


ll solve(int bit_pos, int idx, int prev_b_val_at_this_bit, bool is_equal_to_prev_so_far, bool is_equal_to_m_so_far) {
    // Base case: All numbers' bits at current bit_pos processed
    if (idx == n_global + 1) { 
        // If all bit positions processed, total sum is 0
        if (bit_pos == -1) {
            return 0;
        }
        // Move to the next lower bit, reset to processing b_1.
        // b_1's "previous" number (b_0) is 0, so prev_b_val_at_this_bit is 0.
        // b_1 can start equal to b_0 (is_equal_to_prev_so_far = true).
        // is_equal_to_m_so_far is carried from decisions for b_N at current bit_pos.
        return solve(bit_pos - 1, 1, 0, true, is_equal_to_m_so_far);
    }

    // Base case: If bit_pos < 0, it means we've processed all bits for b_idx...b_N.
    // Their contribution from this point (non-existent bits) is 0.
    if (bit_pos == -1) { 
        return 0;
    }

    tuple<int, int, int, bool, bool> current_state = {bit_pos, idx, prev_b_val_at_this_bit, is_equal_to_prev_so_far, is_equal_to_m_so_far};
    if (memo.count(current_state)) {
        return memo[current_state];
    }

    ll max_total_contribution = LLONG_MIN; 
    bool found_valid_choice = false;

    // Determine range for current_bit_choice_for_b_idx (0 or 1)
    int lower_bound_for_current_bit = 0;
    if (is_equal_to_prev_so_far) { 
        lower_bound_for_current_bit = prev_b_val_at_this_bit;
    }

    int upper_bound_for_current_bit = 1;
    if (idx == n_global && is_equal_to_m_so_far) { 
        upper_bound_for_current_bit = M_bits_global[bit_pos];
    }

    for (int current_bit_choice_for_b_idx = lower_bound_for_current_bit; current_bit_choice_for_b_idx <= upper_bound_for_current_bit; ++current_bit_choice_for_b_idx) {
        
        bool next_overall_is_equal_to_m = is_equal_to_m_so_far;
        if (idx == n_global) { 
            next_overall_is_equal_to_m = is_equal_to_m_so_far && (current_bit_choice_for_b_idx == M_bits_global[bit_pos]);
        }
        
        ll current_term_val = (ll)current_bit_choice_for_b_idx * a_global[idx - 1];
        
        // For b_{idx+1} vs b_{idx}: new `is_equal_to_prev_so_far` is true (they can be equal at this bit initially)
        // new `prev_b_val_at_this_bit` is `current_bit_choice_for_b_idx`
        ll remaining_sum = solve(bit_pos, idx + 1, current_bit_choice_for_b_idx, true, next_overall_is_equal_to_m);
        
        if (remaining_sum != LLONG_MIN) { 
            if (!found_valid_choice || current_term_val + remaining_sum > max_total_contribution) {
                 max_total_contribution = current_term_val + remaining_sum;
            }
            found_valid_choice = true;
        }
    }
    
    return memo[current_state] = (found_valid_choice ? max_total_contribution : LLONG_MIN);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n_global >> m_global;
    a_global.resize(n_global);
    for (int i = 0; i < n_global; ++i) {
        cin >> a_global[i];
    }

    for (int i = 0; i <= 60; ++i) {
        if ((m_global >> i) & 1) {
            M_bits_global[i] = 1;
        } else {
            M_bits_global[i] = 0;
        }
    }
    
    cout << solve(60, 1, 0, true, true) << endl;

    return 0;
}