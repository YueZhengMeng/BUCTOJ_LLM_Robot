/* 文件头注释：动态规划解决组合数学问题，利用模运算优化 */
/* 主要修改标记：[FIX] 优化时间复杂度，处理大规模数据 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAX_K = 100;

// 快速幂函数
long long fast_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// 预处理阶乘和逆元
void preprocess_factorial(vector<long long>& fact, vector<long long>& inv_fact, int max_k) {
    fact[0] = 1;
    for (int i = 1; i <= max_k; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[max_k] = fast_pow(fact[max_k], MOD - 2, MOD);
    for (int i = max_k - 1; i >= 0; --i) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

// 计算组合数 C(n, k)
long long comb(int n, int k, const vector<long long>& fact, const vector<long long>& inv_fact) {
    if (k < 0 || k > n) return 0;
    return (fact[n] * inv_fact[k] % MOD) * inv_fact[n - k] % MOD;
}

int main() {
    int T;
    cin >> T;
    
    // 预处理阶乘和逆元
    vector<long long> fact(MAX_K + 1);
    vector<long long> inv_fact(MAX_K + 1);
    preprocess_factorial(fact, inv_fact, MAX_K);
    
    while (T--) {
        long long N, K;
        cin >> N >> K;
        
        // 特殊情况处理
        if (K == 1) {
            cout << 1 << endl;
            continue;
        }
        if (K > N) {
            cout << 0 << endl;
            continue;
        }
        
        // 计算方案数
        long long result = 0;
        if (N <= MAX_K) {
            // 当N较小时，使用动态规划
            vector<vector<long long>> dp(K + 1, vector<long long>(N, 0));
            dp[0][0] = 1;
            for (int i = 1; i <= K; ++i) {
                for (int j = 0; j < N; ++j) {
                    for (int k = 0; k < N; ++k) {
                        int new_j = (j + k) % N;
                        dp[i][new_j] = (dp[i][new_j] + dp[i - 1][j]) % MOD;
                    }
                }
            }
            result = dp[K][0];
        } else {
            // 当N较大时，使用组合数学公式
            // 方案数为 C(N + K - 1, K) / N
            // 由于N和MOD互质，可以计算模逆元
            long long numerator = comb(N + K - 1, K, fact, inv_fact);
            long long inv_N = fast_pow(N, MOD - 2, MOD);
            result = numerator * inv_N % MOD;
        }
        
        cout << result << endl;
    }
    return 0;
}