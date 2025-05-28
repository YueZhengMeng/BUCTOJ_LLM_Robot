/* 
 * 质数爆炸模拟
 * 关键技术：素数判定+对称变换模拟
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

// Miller-Rabin素性测试（处理大数）
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) d /= 2, ++s;
    
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        ll x = 1, p = a;
        for (ll t = d; t > 0; t >>= 1) {
            if (t & 1) x = (x * p) % n;
            p = (p * p) % n;
        }
        if (x == 1 || x == n - 1) continue;
        
        bool ok = false;
        for (int i = 0; i < s - 1; ++i) {
            x = (x * x) % n;
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

ll next_prime(ll x) {
    if (x < 2) return 2;
    while (true) {
        ++x;
        if (is_prime(x)) return x;
    }
}

int main() {
    ll N, K;
    cin >> N >> K;
    
    ll pos = N;
    while (K--) {
        ll p = next_prime(pos);
        pos = (p + (p - pos)) % MOD;  // 对称变换并取模
    }
    
    cout << pos << endl;
    return 0;
}