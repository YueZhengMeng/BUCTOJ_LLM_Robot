/* 
   Swiss Tournament Simulation (BO1 simplification)
   We greedily pair weak–weak and strong–strong first to maximize weak wins.
   Track states (wins, losses) for weak and strong teams separately.
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;              // number of weak teams
    int sw[4][4] = {}, ss[4][4] = {};  // sw[w][l]: count of weak in state (w,l)
    sw[0][0] = x;
    ss[0][0] = 16 - x;

    int weak_qual = 0;

    // Run up to 5 rounds
    for(int round = 1; round <= 5; round++){
        int sw2[4][4] = {}, ss2[4][4] = {};

        // For each active state (w < 3, l < 3)
        for(int w = 0; w < 3; w++){
            for(int l = 0; l < 3; l++){
                int nW = sw[w][l], nS = ss[w][l];
                if(nW + nS == 0) continue;

                // Greedily pair weak-weak and strong-strong
                int m_WW = nW / 2;               // WW matches
                int m_SS = nS / 2;               // SS matches
                int totalMatches = (nW + nS) / 2;
                int m_SM = totalMatches - m_WW - m_SS;  // cross matches

                // 1) Weak wins come only from WW matches
                //    They move to (w+1, l)
                if(w + 1 == 3){
                    // They hit 3 wins ⇒ qualifiers
                    weak_qual += m_WW;
                } else {
                    sw2[w+1][l] += m_WW;
                }

                // 2) Weak losses come from WW losers and all cross matches
                int weak_losses = m_WW + m_SM;
                if(l + 1 < 3){
                    sw2[w][l+1] += weak_losses;
                }
                // otherwise they are eliminated (l+1 == 3)

                // 3) Strong wins = SS winners + all cross matches
                int strong_wins = m_SS + m_SM;
                if(w + 1 < 3){
                    ss2[w+1][l] += strong_wins;
                }
                // else strong qualifiers (we don't need to count them)

                // 4) Strong losses = SS losers
                if(l + 1 < 3){
                    ss2[w][l+1] += m_SS;
                }
                // else eliminated
            }
        }

        // Swap into current
        memcpy(sw, sw2, sizeof(sw));
        memcpy(ss, ss2, sizeof(ss));
    }

    // Output the maximum number of weak qualifiers
    cout << weak_qual << "\n";
    return 0;
}