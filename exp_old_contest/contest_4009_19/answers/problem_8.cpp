/* 
  Problem: 半排列 (Semi-permutation)
  Technique: Offline sweep from N->1 + Fenwick Tree (BIT) to count 
             number of higher-value occurrences between two positions.
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> t;
    Fenwick(int _n): n(_n), t(n+1, 0) {}
    // add v at position i
    void update(int i, int v) {
        for (; i <= n; i += i & -i)
            t[i] += v;
    }
    // sum of [1..i]
    int query(int i) const {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += t[i];
        return s;
    }
    // sum of [l..r]
    int rangeQuery(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    int M = 2 * N;
    vector<int> a(M+1);
    for(int i = 1; i <= M; i++){
        cin >> a[i];
    }

    // record the two positions of each value 1..N
    vector<array<int,2>> pos(N+1, {0, 0});
    for(int i = 1; i <= M; i++){
        int v = a[i];
        if(pos[v][0] == 0) pos[v][0] = i;
        else pos[v][1] = i;
    }

    Fenwick bit(M);
    long long answer = 0;

    // Process values from N down to 1
    for(int v = N; v >= 1; v--){
        int l = pos[v][0];
        int r = pos[v][1];
        // count how many positions of >v are between l and r
        int cnt = bit.rangeQuery(l+1, r-1);
        answer += cnt;
        // now insert the two occurrences of v into the BIT
        bit.update(l, 1);
        bit.update(r, 1);
    }

    cout << answer << "\n";
    return 0;
}