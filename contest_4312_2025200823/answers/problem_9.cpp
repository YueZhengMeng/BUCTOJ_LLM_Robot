/* 
 * Solution for "刷题统计" (Problem J)
 * Algorithm: Weekly cycle arithmetic + small simulation.
 * Key steps:
 *   1. Compute total problems per week: week_total = 5*a + 2*b.
 *   2. Determine full weeks: weeks = n / week_total.
 *   3. Compute remainder: rem = n % week_total.
 *   4. If remainder is zero, answer is weeks * 7.
 *   5. Otherwise, simulate the next week day-by-day until the cumulative sum covers the remainder.
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll a, b, n;
    cin >> a >> b >> n;
    
    ll week_total = 5 * a + 2 * b;      // problems per week
    ll weeks = n / week_total;          // complete weeks
    ll rem = n % week_total;            // remaining problems after full weeks
    ll days = weeks * 7;                // days from complete weeks
    
    if (rem == 0) {
        cout << days << endl;
        return 0;
    }
    
    // Simulate the next week (at most 7 days)
    ll daily[7] = {a, a, a, a, a, b, b}; // Monday to Sunday
    for (int i = 0; i < 7; ++i) {
        if (rem <= daily[i]) {           // current day can finish the remainder
            days += 1;
            break;
        } else {
            rem -= daily[i];              // solve today's problems
            days += 1;
        }
    }
    
    cout << days << endl;
    return 0;
}