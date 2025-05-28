#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll result = 0;
    for (int bit = 0; bit <= 20; ++bit) {  // 由于 0 <= Ai <= 2^20，最多 20 位
        int mask = 1 << bit;
        int prefix = 0;
        int count[2] = {1, 0};  // count[0] 表示前缀异或和为 0 的次数，count[1] 表示前缀异或和为 1 的次数
        for (int i = 0; i < n; ++i) {
            prefix ^= (a[i] & mask) ? 1 : 0;
            result += (ll)count[prefix ^ 1] * mask;  // 当前前缀异或和为 prefix，与之前的前缀异或和为 prefix ^ 1 的组合
            count[prefix]++;
        }
    }

    cout << result << '\n';
    return 0;
}