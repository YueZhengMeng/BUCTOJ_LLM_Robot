/* Population Standard Deviation Calculation
 * Direct formula implementation with two-pass algorithm
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> nums(n);
    long long sum = 0;
    
    // First pass: read numbers and compute sum
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    
    // Compute mean
    double mean = static_cast<double>(sum) / n;
    
    // Second pass: compute sum of squared differences
    double sqr_diff_sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = nums[i] - mean;
        sqr_diff_sum += diff * diff;
    }
    
    // Final calculation: sqrt(variance)
    double std_dev = sqrt(sqr_diff_sum / n);
    
    // Output with 5 decimal places
    cout << fixed << setprecision(5) << std_dev << endl;
    
    return 0;
}