/* 
  Problem G "铲雪" 
  Key techniques: invariant checking (total sum & checkerboard sum difference mod 4)
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<long long>> h(N, vector<long long>(M));
    long long total = 0;
    long long sumBlack = 0, sumWhite = 0;

    // Read grid and accumulate sums
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> h[i][j];
            total += h[i][j];
            if( (i + j) % 2 == 0 )
                sumBlack += h[i][j];
            else
                sumWhite += h[i][j];
        }
    }

    // 1) Total-sum must be divisible by N*M
    long long cells = 1LL * N * M;
    if(total % cells != 0){
        cout << "No\n";
        return 0;
    }
    long long k = total / cells;

    // 2) Compute the mod-4 invariant on (sumBlack - sumWhite)
    auto mod4 = [&](long long x){
        long long r = x % 4;
        if(r < 0) r += 4;
        return r;
    };
    int diffMod = mod4(sumBlack - sumWhite);

    // 3) Check final configuration condition
    bool ok = false;
    if(cells % 2 == 0){
        // even #cells => #black = #white => final difference = 0
        ok = (diffMod == 0);
    } else {
        // odd #cells => #black = #white + 1 => final difference = k mod 4
        ok = (diffMod == mod4(k));
    }

    cout << (ok ? "Yes\n" : "No\n");
    return 0;
}