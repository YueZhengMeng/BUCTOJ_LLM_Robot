/* 
   Problem: 最少轮数发牌使牌序变为严格递增 (“Straight”)
   Key idea:  A card at initial position pos[x] cannot in one round
   advance more than one index toward its final index x, so it requires
   at least max(0, pos[x] - x) rounds.  Take the maximum over x.
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n), pos(n+1);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        pos[a[i]] = i+1;  // 1-based index
    }
    int ans = 0;
    for(int x = 1; x <= n; x++){
        int diff = pos[x] - x;
        if(diff > ans) ans = diff;
    }
    // If all diff <= 0, answer is 0; else the maximum diff
    cout << ans << "\n";
    return 0;
}