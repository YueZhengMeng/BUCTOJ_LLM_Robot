/* 
  Compute number of ways to choose K distinct numbers from 1..N 
  such that their sum ≡0 mod N, answer mod 998244353.
  Uses roots of unity filter ⇒ sum over divisors of K ∩ divisors of N.
*/
#include <bits/stdc++.h>
using namespace std;
static const int MOD = 998244353;
using int64 = long long;

// fast exponentiation modulo
int64 modpow(int64 a, int64 e = MOD-2) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Precompute factorials and inverses up to MAXK = 100
    const int MAXK = 100;
    vector<int64> fact(MAXK+1,1), ifact(MAXK+1,1);
    for(int i=1;i<=MAXK;i++) fact[i] = fact[i-1]*i % MOD;
    ifact[MAXK] = modpow(fact[MAXK]);
    for(int i=MAXK;i>0;i--) ifact[i-1] = ifact[i]*i % MOD;

    // Precompute primes up to 100 for phi computation
    vector<int> primes;
    vector<bool> sieve(MAXK+1,true);
    for(int i=2;i<=MAXK;i++){
        if(sieve[i]){
            primes.push_back(i);
            for(int j=i*i;j<=MAXK;j+=i) sieve[j] = false;
        }
    }

    int T; 
    cin >> T;
    while(T--){
        int64 N;
        int K;
        cin >> N >> K;

        // enumerate divisors of K
        vector<int> divs;
        for(int d=1; d*d<=K; d++){
            if(K % d == 0){
                divs.push_back(d);
                if(d*d != K) divs.push_back(K/d);
            }
        }

        // accumulator for numerator of formula
        int64 sum = 0;
        for(int d: divs){
            if(N % d) continue;  // d must also divide N
            int64 gcount;       // cnt(d)
            if(d == 1) {
                gcount = 1;
            } else {
                // compute phi(d)
                int tmp = d;
                int phi = d;
                for(int p: primes){
                    if(p*p > tmp) break;
                    if(tmp % p == 0){
                        phi = phi / p * (p-1);
                        while(tmp % p == 0) tmp /= p;
                    }
                }
                if(tmp > 1) phi = phi / tmp * (tmp-1);
                gcount = phi;
            }
            int kd = K / d;    // target size for C(N/d, K/d)
            int64 n_over_d = N / d;

            // compute C(n_over_d, kd) mod
            if(kd > n_over_d){
                continue;  // zero
            }
            int64 cval = 1;
            // falling product numerator
            for(int i=0;i<kd;i++){
                cval = cval * ((n_over_d - i) % MOD) % MOD;
            }
            cval = cval * ifact[kd] % MOD;

            // sign = (-1)^{(d-1)*kd}
            if(((int64)(d-1) * kd) & 1) cval = (MOD - cval) % MOD;

            // accumulate
            sum = (sum + gcount % MOD * cval) % MOD;
        }

        // multiply by inv(N)
        int64 invN = modpow(N % MOD);
        int64 ans = sum * invN % MOD;
        cout << ans << "\n";
    }

    return 0;
}