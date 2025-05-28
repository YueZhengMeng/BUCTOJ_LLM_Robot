/* 文件头注释：计算两个周期性课间时间的重叠时长 */
#include <bits/stdc++.h>
using namespace std;

// 计算最大公约数
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 计算最小公倍数
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int main() {
    int K, x, y, p, q;
    cin >> K >> x >> y >> p >> q;
    
    int total_overlap = 0;
    
    // 计算两个班级的课间周期
    int T1 = x + y;
    int T2 = p + q;
    
    // 计算周期的最小公倍数
    int L = lcm(T1, T2);
    
    // 计算一个周期内的重叠时间
    int overlap_in_period = 0;
    for (int t = 0; t < L; t++) {
        int t1_start = t / T1 * T1 + x;
        int t1_end = t1_start + y;
        int t2_start = t / T2 * T2 + p;
        int t2_end = t2_start + q;
        
        int overlap_start = max(t1_start, t2_start);
        int overlap_end = min(t1_end, t2_end);
        
        if (overlap_start < overlap_end) {
            overlap_in_period += overlap_end - overlap_start;
        }
    }
    
    // 计算完整周期的重叠时间
    int full_periods = K / L;
    total_overlap += full_periods * overlap_in_period;
    
    // 计算剩余时间的重叠时间
    int remaining_time = K % L;
    for (int t = 0; t < remaining_time; t++) {
        int t1_start = t / T1 * T1 + x;
        int t1_end = t1_start + y;
        int t2_start = t / T2 * T2 + p;
        int t2_end = t2_start + q;
        
        int overlap_start = max(t1_start, t2_start);
        int overlap_end = min(t1_end, t2_end);
        
        if (overlap_start < overlap_end && overlap_start < K) {
            total_overlap += min(overlap_end, K) - overlap_start;
        }
    }
    
    cout << total_overlap << endl;
    return 0;
}