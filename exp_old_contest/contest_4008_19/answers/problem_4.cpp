/* 
  Solve balloon‐reduction game by parity invariants:
  Removal of AA doesn't change color‐count parity.
  Replacement X->YZ flips all three parities.
  We can reach final (1,0,0) iff initial parity is (1,0,0) or (0,1,1).
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int N = s.size();

    // prefix sums for R, G, B
    vector<int> preR(N+1, 0), preG(N+1, 0), preB(N+1, 0);
    for (int i = 0; i < N; i++) {
        preR[i+1] = preR[i] + (s[i] == 'R');
        preG[i+1] = preG[i] + (s[i] == 'G');
        preB[i+1] = preB[i] + (s[i] == 'B');
    }

    int Q;
    cin >> Q;
    string ans;
    ans.reserve(Q);

    while (Q--) {
        int L, R;
        cin >> L >> R;
        // get counts in [L,R]
        int cR = preR[R] - preR[L-1];
        int cG = preG[R] - preG[L-1];
        int cB = preB[R] - preB[L-1];

        // compute parity
        int pR = cR & 1;
        int pG = cG & 1;
        int pB = cB & 1;
        // check if (pR,pG,pB) == (1,0,0) or (0,1,1)
        bool ok = (pR==1 && pG==0 && pB==0) || (pR==0 && pG==1 && pB==1);
        ans.push_back(ok ? 'Y' : 'N');
    }

    cout << ans << "\n";
    return 0;
}