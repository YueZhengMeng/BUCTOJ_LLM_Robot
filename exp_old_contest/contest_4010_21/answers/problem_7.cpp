/* 文件头注释：利用数学公式求解忘记加上的楼层编号 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long S_prime;
        cin >> S_prime;

        // 计算 n 的近似值，n^2 + n - 2S' = 0
        long long n = (sqrt(1 + 8 * S_prime) - 1) / 2;

        // 计算 S = n(n+1)/2
        long long S = n * (n + 1) / 2;

        // 计算 x = S - S'
        long long x = S - S_prime;

        // 如果 x 不在 1 到 n 之间，说明 n 需要加 1
        if (x < 1 || x > n) {
            n++;
            S = n * (n + 1) / 2;
            x = S - S_prime;
        }

        cout << x << '\n';
    }

    return 0;
}