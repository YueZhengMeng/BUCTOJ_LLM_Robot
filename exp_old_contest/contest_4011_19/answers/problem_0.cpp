/* 
   Convert an integer (≤100,000,000) into Chinese pinyin reading.
   Key techniques: split into 'wan' segment and low 4-digit segment,
   careful zero‐handling, and special omit‐"yi" rule for leading "shi".
*/
#include <bits/stdc++.h>
using namespace std;

// digit to pinyin
const string DIG[10] = {
    "ling","yi","er","san","si","wu","liu","qi","ba","jiu"
};
// units for positions within a 4‐digit group
// idx 0->thousands,1->hundreds,2->tens,3->ones
const string UNIT[4] = {
    "qian","bai","shi",""
};

// Convert a 1..9999 number into pinyin words.
// omitOneTen==true → if the first nonzero digit is a '1' in tens place, omit "yi".
vector<string> convertGroup(int x, bool omitOneTen) {
    vector<string> res;
    bool started = false;    // have we printed any digit/unit yet?
    bool needZero = false;   // saw a zero after starting, so next nonzero must insert "ling"
    int d[4] = {
        x / 1000 % 10,
        x / 100  % 10,
        x / 10   % 10,
        x       % 10
    };
    for (int i = 0; i < 4; i++) {
        int digit = d[i];
        if (digit != 0) {
            if (needZero && started) {
                res.push_back("ling");
                needZero = false;
            }
            // special omit "yi" in "yi shi" if this is the very first print
            if (i == 2 && digit == 1 && !started && omitOneTen) {
                res.push_back(UNIT[i]);
            } else {
                res.push_back(DIG[digit]);
                if (!UNIT[i].empty())
                    res.push_back(UNIT[i]);
            }
            started = true;
        } else {
            if (started) {
                needZero = true;
            }
        }
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<string> ans;
        if (n == 100000000) {
            // exactly 10^8
            ans = {"yi","yi"};
        } else if (n == 0) {
            ans = {"ling"};
        } else {
            int high = n / 10000;
            int low  = n % 10000;
            // process high group (wan)
            if (high > 0) {
                auto hw = convertGroup(high, true);
                ans.insert(ans.end(), hw.begin(), hw.end());
                ans.push_back("wan");
            }
            // insert "ling" if needed between high and low groups
            if (low > 0) {
                if (high > 0 && (low < 1000 || high % 10 == 0)) {
                    ans.push_back("ling");
                }
                // for low group, omitOneTen only if high==0
                bool omitLow = (high == 0);
                auto lw = convertGroup(low, omitLow);
                ans.insert(ans.end(), lw.begin(), lw.end());
            }
        }
        // output with single spaces
        for (int i = 0; i < (int)ans.size(); i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }
    return 0;
}