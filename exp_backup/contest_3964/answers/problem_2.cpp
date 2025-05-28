#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string num;
    cin >> num;
    int n = num.size();
    int ans = 0;

    // 枚举所有可能的子串
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // 比较反转后的子串与原子串的字典序
            int left = i, right = j;
            while (left < right) {
                if (num[left] != num[right]) {
                    if (num[left] > num[right]) {
                        ++ans;
                    }
                    break;
                }
                ++left;
                --right;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}