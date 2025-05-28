/* 比特彩票最大奖金计算 - 改进的贪心bit分配策略 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    ll m;
    cin >> n >> m;
    
    vector<pair<ll, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    
    // 按绝对值降序排序，优先处理影响大的系数
    sort(a.begin(), a.end(), [](const auto& x, const auto& y) {
        return abs(x.first) > abs(y.first);
    });
    
    vector<ll> b(n, 0);
    ll low = 0;
    
    // 处理正系数：尽可能分配高bit位
    for (int bit_pos = 60; bit_pos >= 0; --bit_pos) {
        ll bit = 1LL << bit_pos;
        if ((low | bit) > m) continue;
        
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i].first > 0 && (b[a[i].second] & bit) == 0 && (low | bit) <= m) {
                b[a[i].second] |= bit;
                low |= bit;
                break; // 每次只分配一个最高位，保证严格递增
            }
        }
    }
    
    // 处理负系数：尽可能不分配高bit位
    for (int i = 0; i < n; ++i) {
        if (a[i].first <= 0) {
            // 找到最小的未设置bit位
            ll val = 0;
            for (int j = 0; j < 61; ++j) {
                ll candidate = b[a[i].second] | (1LL << j);
                if (candidate > m) continue;
                if (j == 0 || (candidate > (a[i].second > 0 ? b[a[i].second-1] : -1))) {
                    val = candidate;
                    break;
                }
            }
            b[a[i].second] = val;
        }
    }
    
    // 确保严格递增
    for (int i = 1; i < n; ++i) {
        if (b[i] <= b[i-1]) {
            b[i] = b[i-1] + 1;
        }
    }
    
    // 计算最终结果
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        res += a[i].first * __builtin_popcountll(b[i]);
    }
    
    cout << res << endl;
    return 0;
}