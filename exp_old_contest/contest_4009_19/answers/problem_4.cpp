/* 
   Hero Proficiency Zeroing
   1) Solve linear system for total picks of Y/M/L so that two heroes end at 0.
   2) Greedily schedule moves ensuring no immediate or future negative levels.
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int init[3];
    // 0=Y, 1=M, 2=L
    cin >> init[0] >> init[1] >> init[2];

    int active = -1;
    int rem[3] = {0,0,0};
    // Try each hero as the one that survives (others go to zero)
    for(int k=0;k<3 && active<0;k++){
        int i=(k+1)%3, j=(k+2)%3;
        int sum = init[i] + init[j];
        if(sum % 2 != 0) continue;
        // total picks for active = c
        int c = sum/2;
        // difference for picks of i vs j
        int diff = (init[j] - init[i]) / 2;
        // pick count for i = a, for j = b = a - diff
        // smallest non-negative a is max(diff,0)
        int a = max(diff, 0);
        int b = a - diff;
        // validate non-negative
        if(a<0 || b<0) continue;
        rem[i] = a;
        rem[j] = b;
        rem[k] = c;
        active = k;
    }
    if(active<0){
        cout << -1;
        return 0;
    }
    int cur[3] = { init[0], init[1], init[2] };
    string ans;
    ans.reserve(300);

    auto canPick = [&](int x, int cur2[3], int rem2[3]) {
        // simulate move x
        int tmpCur[3]   = { cur2[0], cur2[1], cur2[2] };
        int tmpRem[3]   = { rem2[0], rem2[1], rem2[2] };
        tmpCur[x]++; 
        for(int h=0;h<3;h++){
            if(h==x) continue;
            tmpCur[h]--;
            if(tmpCur[h]<0) return false;
        }
        tmpRem[x]--;
        int futureMoves = tmpRem[0] + tmpRem[1] + tmpRem[2];
        // check inevitable future decrements
        for(int h=0;h<3;h++){
            int futureDec = futureMoves - tmpRem[h];
            if(tmpCur[h] < futureDec) return false;
        }
        return true;
    };

    // Build sequence
    while(rem[0]+rem[1]+rem[2] > 0){
        bool moved = false;
        // try picks in order of descending rem[] to tend to finish large buckets sooner
        vector<int> order = {0,1,2};
        sort(order.begin(), order.end(), [&](int a, int b){
            return rem[a] > rem[b];
        });
        for(int x: order){
            if(rem[x]<=0) continue;
            if(canPick(x, cur, rem)){
                // apply move
                cur[x]++;
                for(int h=0;h<3;h++) if(h!=x) cur[h]--;
                rem[x]--;
                ans.push_back("YML"[x]);
                moved = true;
                break;
            }
        }
        if(!moved){
            // should not happen if solution exists
            cout << -1;
            return 0;
        }
    }

    if(ans.size() > 1000) {
        cout << -1;
    } else {
        cout << ans;
    }
    return 0;
}