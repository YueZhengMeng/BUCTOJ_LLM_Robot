/* 
   Problem: Count for each student how many others share the same
   DSU component in ALL k courses.  
   Techniques: k×DSU to get per-course roots, then hash each student's
   root-signature into two 64-bit values and sort by that for grouping.
*/
#include <bits/stdc++.h>
using namespace std;

// Simple Union-Find (DSU) with path compression & union by rank
struct DSU {
    vector<int> p, r;
    DSU(int n): p(n), r(n,0) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return p[x] == x ? x : (p[x] = find(p[x]));
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // Two rolling hashes per student
    const uint64_t B1 = 91138233, B2 = 97266353;
    vector<uint64_t> h1(n, 0), h2(n, 0);

    // Build hash-signatures course by course
    for (int course = 0; course < k; course++) {
        int m; 
        cin >> m;
        DSU dsu(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            dsu.unite(u, v);
        }
        // Incorporate this course's root into each student's hash
        for (int s = 0; s < n; s++) {
            uint64_t r = (uint64_t)(dsu.find(s) + 1);
            h1[s] = h1[s] * B1 + r;
            h2[s] = h2[s] * B2 + r;
        }
    }

    // Prepare (h1,h2,index) for sorting
    struct Sig { uint64_t h1, h2; int idx; };
    vector<Sig> vs(n);
    for (int i = 0; i < n; i++) {
        vs[i] = { h1[i], h2[i], i };
    }
    // C++11-compatible comparator
    sort(vs.begin(), vs.end(),
         [](const Sig &a, const Sig &b) {
             if (a.h1 != b.h1) return a.h1 < b.h1;
             return a.h2 < b.h2;
         });

    // Group identical signatures and assign counts
    vector<int> ans(n);
    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (i == n || vs[i].h1 != vs[i-1].h1 || vs[i].h2 != vs[i-1].h2) {
            int groupSize = i - start;
            for (int j = start; j < i; j++) {
                ans[vs[j].idx] = groupSize;
            }
            start = i;
        }
    }

    // Output
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i+1<n ? ' ' : '\n');
    }
    return 0;
}