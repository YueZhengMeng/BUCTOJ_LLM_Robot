/*  
   Problem C: 魅惑菇 (Charming Mushrooms)  
   Fix: replace “bulk‐fight” transitions by atomic fight (cost=0) and single‐charm (cost=1) edges,
   then run a 0–1 BFS over states (pos, h), where h is the residual hp of the current enemy head.
   Reduced memory by using 16‐bit dist and fhead tables.
*/
#include <bits/stdc++.h>
#include <cstdint>
using namespace std;
using pii = pair<int,int>;
static const int INF_INT = 0x3f3f3f3f;
static const int HMAX = 6400;
// maximum number of positions (n up to ~2000, plus sentinel)
static const int PMAX = 2005;
// INF for uint16_t arrays: must exceed any real answer (≤n≤2000)
static const uint16_t INF16 = 0x3FFF;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> hp(n+2, 0);
    for(int i = 1; i <= n; i++){
        cin >> hp[i];
    }

    // dist[pos][h] = min charms to reach enemy state (pos,h)
    // h==0 means no partial head; the real head is hp[pos].
    static uint16_t dist[PMAX][HMAX+1];
    static uint16_t fhead[PMAX][HMAX+1];  // current friendly‐head hp (0 if none)

    // initialize dist to INF16
    for(int i = 1; i <= n+1; i++){
        for(int h = 0; h <= HMAX; h++){
            dist[i][h] = INF16;
        }
    }
    // fhead is static => zeroed

    deque<pii> dq;
    dist[1][0] = 0;
    dq.emplace_back(1, 0);

    while(!dq.empty()){
        auto [pos, h] = dq.front();
        dq.pop_front();
        int curd = dist[pos][h];
        // goal: enemy queue empty => pos==n+1 and h==0
        if(pos == n+1 && h == 0){
            cout << curd << "\n";
            return 0;
        }
        // friendly head and enemy head
        int f = fhead[pos][h];
        int e = (h > 0 ? h : (pos <= n ? hp[pos] : 0));

        // 1) Fight transition (cost=0)
        if(f > 0 && e > 0){
            int nf = f, ne = e;
            if(nf > ne){
                nf -= ne;
                ne = 0;
            } else if(ne > nf){
                ne -= nf;
                nf = 0;
            } else {
                nf = ne = 0;
            }
            int npos = pos;
            int nh  = ne;
            if(ne == 0){
                if(h > 0){
                    nh = 0;
                } else {
                    npos++;
                    nh = 0;
                }
            }
            int nfhead = nf;  // 0 if nf==0
            if(dist[npos][nh] > curd){
                dist[npos][nh] = curd;
                fhead[npos][nh] = nfhead;
                dq.emplace_front(npos, nh);
            }
        }

        // 2) Charm transition (cost=1)
        if(e > 0){
            int npos = pos, nh = h;
            int pulled = 0;
            if(h > 0){
                pulled = h;
                nh = 0;
            } else if(pos <= n){
                pulled = hp[pos];
                npos++;
                nh = 0;
            }
            if(pulled > 0){
                int nfhead = pulled;
                if(curd + 1 < dist[npos][nh]){
                    dist[npos][nh] = curd + 1;
                    fhead[npos][nh] = nfhead;
                    dq.emplace_back(npos, nh);
                }
            }
        }
    }

    // unreachable
    cout << "-1\n";
    return 0;
}