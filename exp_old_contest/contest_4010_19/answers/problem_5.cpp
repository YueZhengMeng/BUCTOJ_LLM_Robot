/* 
  Algorithm: DP with prefix‐sums and binary search per row 
  Key idea: dp[i][j] = sum of dp[i-1][k] for all a[i-1][k] < a[i][j].
  Use sorted rows + prefix sums + upper_bound.
*/
#include <bits/stdc++.h>
using namespace std;
static const int MOD = 19260817;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> a(N, vector<int>(M));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
    }

    // dp_prev[j]: dp value for previous row picking a[i-1][j]
    vector<int> dp_prev(M, 1), dp_curr(M);
    // Base case: for row 0, dp_prev[j] = 1

    for(int i = 1; i < N; i++){
        // build prefix sums of dp_prev
        vector<int> pref(M+1, 0);
        for(int j = 0; j < M; j++){
            pref[j+1] = pref[j] + dp_prev[j];
            if(pref[j+1] >= MOD) pref[j+1] -= MOD;
        }
        // compute dp_curr for row i
        for(int j = 0; j < M; j++){
            // Find how many in a[i-1] are strictly < a[i][j]
            int cnt = upper_bound(a[i-1].begin(), a[i-1].end(), a[i][j] - 1)
                      - a[i-1].begin();
            dp_curr[j] = pref[cnt];
        }
        // swap dp_curr and dp_prev for next iteration
        dp_prev.swap(dp_curr);
    }

    // Sum up dp_prev over the last row
    int answer = 0;
    for(int v : dp_prev){
        answer += v;
        if(answer >= MOD) answer -= MOD;
    }
    cout << answer << "\n";
    return 0;
}