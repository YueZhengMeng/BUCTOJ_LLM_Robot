/* 
  Compute subtree-LCMs in a rooted tree by DSU-on-tree (small-to-large merging).
  Each node’s value is factorized; we maintain for each subtree the max exponent
  of each prime and update the LCM mod 998244353 on the fly.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static const int MAXA = 500000;
static const int MOD = 998244353;

// fast exponentiation mod
ll modpow(ll a, ll e) {
    ll r = 1;
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

    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++) cin >> a[i];

    // read tree edges, build children list
    vector<vector<int>> children(n+1);
    for(int u = 2, p; u <= n; u++){
        cin >> p;
        children[p].push_back(u);
    }

    // 1) Linear sieve for smallest prime factor
    vector<int> spf(MAXA+1);
    vector<int> primes;
    for(int i = 2; i <= MAXA; i++){
        if(!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for(int p: primes){
            ll x = ll(i)*p;
            if(x > MAXA) break;
            spf[x] = p;
            if(p == spf[i]) break;
        }
    }
    // 2) Pre-factor all a[i]
    vector<vector<pair<int,int>>> fac(n+1);
    for(int i = 1; i <= n; i++){
        int x = a[i];
        while(x > 1){
            int p = spf[x], cnt = 0;
            while(x % p == 0){ x /= p; cnt++; }
            fac[i].push_back({p, cnt});
        }
    }

    // 3) Compute post-order iteratively
    vector<int> post;
    post.reserve(n);
    vector<pair<int,int>> stk;
    stk.reserve(n);
    stk.emplace_back(1, 0);
    while(!stk.empty()){
        auto &tp = stk.back();
        int u = tp.first;
        int &idx = tp.second;
        if(idx < (int)children[u].size()){
            int v = children[u][idx++];
            stk.emplace_back(v, 0);
        } else {
            post.push_back(u);
            stk.pop_back();
        }
    }

    // 4) DSU-on-tree merge
    vector<map<int,int>*> mp(n+1, nullptr);
    vector<ll> subtreeLcm(n+1, 1), ans(n+1, 1);

    for(int u: post){
        // if leaf => start new map
        if(children[u].empty()){
            mp[u] = new map<int,int>();
            subtreeLcm[u] = 1;
        } else {
            // pick the child with largest map
            int bigC = children[u][0];
            for(int v: children[u]){
                if(mp[v]->size() > mp[bigC]->size())
                    bigC = v;
            }
            mp[u] = mp[bigC];
            subtreeLcm[u] = subtreeLcm[bigC];
            // merge others into bigC
            for(int v: children[u]){
                if(v == bigC) continue;
                for(auto &pe: *mp[v]){
                    int p = pe.first, e = pe.second;
                    auto it = mp[u]->find(p);
                    if(it == mp[u]->end()){
                        (*mp[u])[p] = e;
                        subtreeLcm[u] = subtreeLcm[u] * modpow(p, e) % MOD;
                    } else if(it->second < e){
                        int delta = e - it->second;
                        it->second = e;
                        subtreeLcm[u] = subtreeLcm[u] * modpow(p, delta) % MOD;
                    }
                }
                delete mp[v];
            }
        }
        // incorporate u's own factors
        for(auto &pe: fac[u]){
            int p = pe.first, e = pe.second;
            auto it = mp[u]->find(p);
            if(it == mp[u]->end()){
                (*mp[u])[p] = e;
                subtreeLcm[u] = subtreeLcm[u] * modpow(p, e) % MOD;
            } else if(it->second < e){
                int delta = e - it->second;
                it->second = e;
                subtreeLcm[u] = subtreeLcm[u] * modpow(p, delta) % MOD;
            }
        }
        ans[u] = subtreeLcm[u];
    }

    // 5) Answer queries online
    ll lastans = 0;
    for(int i = 0, x; i < q; i++){
        cin >> x;
        int u = (int)((x + lastans) % n) + 1;
        lastans = ans[u];
        cout << lastans << "\n";
    }
    return 0;
}