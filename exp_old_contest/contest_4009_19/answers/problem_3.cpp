/* 
  Sum of squared distances between all ordered pairs:
  ∑₍i,j₎[(xᵢ−xⱼ)² + (yᵢ−yⱼ)²]
  = 2N*(∑xᵢ²+∑yᵢ²) - 2*( (∑xᵢ)² + (∑yᵢ)² )  (mod 998244353)
*/
#include <bits/stdc++.h>
using namespace std;
static const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    long long sumX = 0, sumY = 0;
    long long sumX2 = 0, sumY2 = 0;
    for (int i = 0; i < N; i++) {
        long long x, y;
        cin >> x >> y;
        // bring into [0, MOD)
        x %= MOD; if (x < 0) x += MOD;
        y %= MOD; if (y < 0) y += MOD;
        sumX  = (sumX  + x)    % MOD;
        sumY  = (sumY  + y)    % MOD;
        sumX2 = (sumX2 + x*x%MOD) % MOD;
        sumY2 = (sumY2 + y*y%MOD) % MOD;
    }

    // 2N * (sumX2 + sumY2)
    long long term1 = (2LL * N % MOD) * ((sumX2 + sumY2) % MOD) % MOD;
    // 2 * ( (sumX)^2 + (sumY)^2 )
    long long sumSq = ( (sumX * sumX) % MOD + (sumY * sumY) % MOD ) % MOD;
    long long term2 = (2 * sumSq) % MOD;

    long long ans = (term1 - term2) % MOD;
    if (ans < 0) ans += MOD;

    cout << ans << "\n";
    return 0;
}