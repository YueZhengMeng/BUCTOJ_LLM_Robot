#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For memset
#include <algorithm>

using namespace std;

string S; // String representation of N
int K_target; // Target count of non-zero digits
long long memo[105][5][2][2]; // memo[idx][count_k][tight][is_leading]

// idx: current digit position we are considering (from left, 0-indexed)
// count_k: number of non-zero digits placed so far
// tight: boolean, true if we are restricted by the digits of S (i.e., current prefix matches prefix of S)
// is_leading: boolean, true if we are currently placing leading zeros (all digits placed so far were 0, or no digits placed yet)
long long solve(int idx, int count_k, bool tight, bool is_leading) {
    // Pruning: if we already have more than K_target non-zero digits
    if (count_k > K_target) {
        return 0;
    }

    // Base case: all digits of S (representing N) have been processed
    if (idx == S.length()) {
        // If we have exactly K_target non-zero digits, we found a valid number.
        // If is_leading is still true at this point, it means the number formed was composed entirely of zeros (e.g., "0", "00").
        // In such a case, count_k would be 0.
        // Since K_target >= 1 (as per problem constraints), a number like "0" (with count_k=0) will not satisfy count_k == K_target.
        // This correctly ensures that we count numbers with K_target non-zero digits.
        return (count_k == K_target) ? 1 : 0;
    }

    // Return memoized result if available
    if (memo[idx][count_k][tight][is_leading] != -1) {
        return memo[idx][count_k][tight][is_leading];
    }

    long long ans = 0;
    // Determine the upper limit for the current digit
    // If tight is true, current digit can go up to S[idx]
    // Otherwise, it can go up to 9
    int upper_bound = tight ? (S[idx] - '0') : 9;

    for (int digit = 0; digit <= upper_bound; ++digit) {
        // new_tight will be true if the original tight was true AND we pick the maximal allowed digit (S[idx])
        bool new_tight = tight && (digit == upper_bound);

        if (is_leading && digit == 0) {
            // Case 1: Still in the leading zeros phase, and placing a zero.
            // - count_k (non-zero count) does not change.
            // - is_leading remains true.
            ans += solve(idx + 1, count_k, new_tight, true);
        } else {
            // Case 2: No longer in leading zeros phase, OR placing a non-zero digit.
            // - Update count_k: increment if the current digit is non-zero.
            // - is_leading becomes false (once a non-zero digit is placed, or if we were already past leading zeros).
            ans += solve(idx + 1, count_k + (digit != 0), new_tight, false);
        }
    }

    return memo[idx][count_k][tight][is_leading] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S >> K_target;

    memset(memo, -1, sizeof(memo));

    // The function `solve(0, 0, true, true)` counts numbers x such that 0 <= x <= N
    // and x has K_target non-zero digits.
    // Since the problem constraint is 1 <= K_target <= 3, the number 0 (which has 0 non-zero digits)
    // will not be counted by the `solve` function (as count_k will be 0, and 0 != K_target).
    // Therefore, the result directly gives the count of integers in the range [1, N] satisfying the condition.
    long long result = solve(0, 0, true, true);

    cout << result << endl;

    return 0;
}