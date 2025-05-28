/* 
  Optimal Cache Replacement (Belady's algorithm)
  - Precompute next occurrence for each position
  - Use a set to track (next_occurrence, manga_id) on desk
  - Evict the one with farthest next use on a miss when full
*/
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
const int INF = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    // Compute next occurrence for each position
    vector<int> nextOcc(n+2, INF), lastOcc(n+2, INF);
    for(int i = n; i >= 1; i--){
        nextOcc[i] = lastOcc[a[i]];
        lastOcc[a[i]] = i;
    }

    // Track which mangas are on desk and their current next index
    vector<bool> onDesk(n+2, false);
    vector<int> curNext(n+2, INF);
    set<pii> desk;  // sorted by (next_occurrence, manga_id)

    long long fetches = 0;
    for(int i = 1; i <= n; i++){
        int manga = a[i];
        int nxt = nextOcc[i];
        if(onDesk[manga]){
            // Update its next‐use index in the set
            desk.erase({curNext[manga], manga});
            curNext[manga] = nxt;
            desk.insert({curNext[manga], manga});
        } else {
            // Miss: need to fetch
            fetches++;
            if((int)desk.size() == m){
                // Evict the one with largest next‐use
                auto it = prev(desk.end());
                onDesk[it->second] = false;
                desk.erase(it);
            }
            // Insert current manga
            onDesk[manga] = true;
            curNext[manga] = nxt;
            desk.insert({nxt, manga});
        }
    }

    cout << fetches << "\n";
    return 0;
}