#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> skills(N);
    for (int i = 0; i < N; ++i) {
        cin >> skills[i].first >> skills[i].second;
    }

    // 二分查找确定阈值 x
    auto check = [&](ll x) -> bool {
        ll cnt = 0;
        for (auto& [A, B] : skills) {
            if (A >= x) {
                cnt += (A - x) / B + 1;
                if (cnt >= M) return true;
            }
        }
        return cnt >= M;
    };

    ll left = 0, right = 1e12;
    while (left < right) {
        ll mid = (left + right + 1) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    // 计算总收益
    ll total = 0;
    ll cnt = 0;
    for (auto& [A, B] : skills) {
        if (A >= left) {
            ll n = (A - left) / B + 1;
            cnt += n;
            total += n * A - n * (n - 1) / 2 * B;
        }
    }

    // 处理可能的多余升级次数
    if (cnt > M) {
        total -= (cnt - M) * left;
    }

    cout << total << endl;

    return 0;
}