/* 
  Problem E: Prime Explosion
  - Sieve up to MAX to find all primes.
  - Build nextPrime[] for O(1) successor-prime queries.
  - Simulate K jumps: x <- 2*p(x+1) - x.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const int MAX = 2000000;
static const int MOD = 1000000007;

bitset<MAX+1> is_prime;
int nextPrimeArr[MAX+2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    // 1) Sieve of Eratosthenes up to MAX
    is_prime.set(); 
    is_prime[0] = is_prime[1] = 0;
    for(int i = 2; (ll)i*i <= MAX; i++){
        if(is_prime[i]){
            for(int j = i*i; j <= MAX; j += i)
                is_prime[j] = 0;
        }
    }

    // 2) Build nextPrimeArr[i] = smallest prime >= i (or -1 if none)
    nextPrimeArr[MAX] = is_prime[MAX] ? MAX : -1;
    for(int i = MAX-1; i >= 0; i--){
        if(is_prime[i]) nextPrimeArr[i] = i;
        else nextPrimeArr[i] = nextPrimeArr[i+1];
    }

    // 3) Simulate K jumps
    ll x = N;
    for(int step = 0; step < K; step++){
        // Find p = smallest prime > x
        int idx = x + 1;
        if(idx > MAX || nextPrimeArr[idx] == -1){
            // Should not happen with our MAX, but guard for safety
            // Fallback: linear scan (very unlikely to be needed)
            int p = idx;
            auto isPrimeSmall = [&](int y){
                if(y < 2) return false;
                for(int d = 2; (ll)d*d <= y; d++){
                    if(y % d == 0) return false;
                }
                return true;
            };
            while(!isPrimeSmall(p)) p++;
            x = 2LL*p - x;
        } else {
            int p = nextPrimeArr[idx];
            x = 2LL*p - x;
        }
        // x remains small (< ~1.4e6), so no overflow
    }

    // 4) Output result mod 1e9+7
    cout << (x % MOD + MOD) % MOD << "\n";
    return 0;
}