/* 
   BFS on bitmask states to check if A can be transformed to B by toggles:
   - 4 row flips, 4 column flips, 9 2×2 square flips.
   - State space: 2^16 configurations; edges by XOR with one of 17 masks.
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read boards A and B, flatten into 16-bit masks
    int A_mask = 0, B_mask = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int x; 
            cin >> x;
            if(x) A_mask |= (1 << (4*i + j));
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int x; 
            cin >> x;
            if(x) B_mask |= (1 << (4*i + j));
        }
    }

    // The required delta mask
    int target = A_mask ^ B_mask;
    if(target == 0) {
        cout << "Yes\n";
        return 0;
    }

    // Precompute the 17 toggle masks
    vector<int> masks;
    // 4 row flips
    for(int r = 0; r < 4; r++){
        int m = 0;
        for(int c = 0; c < 4; c++){
            m |= (1 << (4*r + c));
        }
        masks.push_back(m);
    }
    // 4 column flips
    for(int c = 0; c < 4; c++){
        int m = 0;
        for(int r = 0; r < 4; r++){
            m |= (1 << (4*r + c));
        }
        masks.push_back(m);
    }
    // 9 sub-square flips (2x2)
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            int m = 0;
            m |= (1 << (4*r + c));
            m |= (1 << (4*r + (c+1)));
            m |= (1 << (4*(r+1) + c));
            m |= (1 << (4*(r+1) + (c+1)));
            masks.push_back(m);
        }
    }

    // BFS from state 0 to see if we can reach 'target'
    const int MAXS = 1 << 16;
    vector<bool> vis(MAXS, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;

    while(!q.empty()) {
        int s = q.front(); q.pop();
        for(int m : masks) {
            int ns = s ^ m;
            if(!vis[ns]) {
                if(ns == target) {
                    cout << "Yes\n";
                    return 0;
                }
                vis[ns] = true;
                q.push(ns);
            }
        }
    }

    cout << "No\n";
    return 0;
}