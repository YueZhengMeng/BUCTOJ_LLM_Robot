/* 
   Palindrome Pairs via Trie of reversed strings + rolling-hash for palindrome checks.
   For each reversed string, we store at each node the indices of strings whose 
   remaining prefix is a palindrome. Then query each string A against the trie 
   to find partners B such that A+B is a palindrome. 
*/
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

static const ull BASE = 91138233ULL;
static const ull MOD  = 1000000007ULL;

// Trie node
struct Node {
    int nxt[26];
    int word_id;                  // index of word ending exactly here, or -1
    vector<int> pal_suf_ids;      // indices j of words B such that the remaining suffix of reversed B is palindrome
    Node() {
        memset(nxt, -1, sizeof(nxt));
        word_id = -1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n);
    for(int i = 0; i < n; i++){
        cin >> words[i];
    }
    // Precompute powers
    int MAXL = 0;
    for(auto &s: words) if((int)s.size() > MAXL) MAXL = s.size();
    vector<ull> power(MAXL+1, 1);
    for(int i = 1; i <= MAXL; i++){
        power[i] = (power[i-1] * BASE) % MOD;
    }

    // For each word: build forward-hash and reverse-hash
    vector< vector<ull> > h_s(n), h_t(n);
    for(int i = 0; i < n; i++){
        string &s = words[i];
        int m = s.size();
        // forward hash of s
        h_s[i].assign(m+1, 0);
        for(int j = 0; j < m; j++){
            h_s[i][j+1] = (h_s[i][j] * BASE + (ull)(s[j])) % MOD;
        }
        // build reversed
        string t = s;
        reverse(t.begin(), t.end());
        h_t[i].assign(m+1, 0);
        for(int j = 0; j < m; j++){
            h_t[i][j+1] = (h_t[i][j] * BASE + (ull)(t[j])) % MOD;
        }
    }

    // Helper to get hash(s[l..r]) in O(1), 0-based, inclusive
    auto getHash = [&](const vector<ull> &hf, int l, int r)->ull {
        // hf[k] = hash of prefix length k
        ull res = (hf[r+1] + MOD 
                  - (hf[l] * power[r-l+1]) % MOD ) % MOD;
        return res;
    };

    // Build Trie
    vector<Node> trie;
    trie.reserve(500000 + 5);
    trie.emplace_back(); // root

    for(int idx = 0; idx < n; idx++){
        const string &s = words[idx];
        int m = s.size();
        // Precompute palindromic-prefix flags of s:
        // pal_pref_len[L] = s[0..L-1] is palindrome
        vector<bool> pal_pref(m+1, false);
        pal_pref[0] = true; // empty
        for(int L = 1; L <= m; L++){
            // compare s[0..L-1] with its reverse, which is t[m-L..m-1]
            ull h1 = getHash(h_s[idx], 0, L-1);
            ull h2 = getHash(h_t[idx], m-L, m-1);
            pal_pref[L] = (h1 == h2);
        }
        // We're inserting rev(s)=t into trie; at step k (0..m):
        // If remaining prefix length = m-k is palindrome -> store idx
        int node = 0;
        for(int k = 0; k < m; k++){
            if(pal_pref[m - k]) {
                trie[node].pal_suf_ids.push_back(idx);
            }
            int c = s[m-1-k] - 'a';  // char of reversed
            if(trie[node].nxt[c] == -1) {
                trie[node].nxt[c] = (int)trie.size();
                trie.emplace_back();
            }
            node = trie[node].nxt[c];
        }
        // At end of entire reversed string
        trie[node].pal_suf_ids.push_back(idx);
        trie[node].word_id = idx;
    }

    // Now query each word A against the trie
    int answer = 0;
    for(int idx = 0; idx < n; idx++){
        const string &s = words[idx];
        int m = s.size();
        // Precompute palindromic-suffix flags: pal_suf[k] = s[k..m-1] is palindrome
        vector<bool> pal_suf(m+1, false);
        pal_suf[m] = true; // empty suffix
        for(int k = 0; k < m; k++){
            // s[k..m-1] vs its reverse: t[0..m-k-1]
            ull h1 = getHash(h_s[idx], k, m-1);
            ull h2 = getHash(h_t[idx], 0, m-k-1);
            pal_suf[k] = (h1 == h2);
        }

        // walk the trie along s
        int node = 0;
        for(int k = 0; k < m; k++){
            // If node marks a full word_id j != idx, and the rest s[k..] is palindrome
            int j = trie[node].word_id;
            if(j >= 0 && j != idx && pal_suf[k]){
                answer = max(answer, m + (int)words[j].size());
            }
            int c = s[k] - 'a';
            if(trie[node].nxt[c] == -1) {
                node = -1;
                break;
            }
            node = trie[node].nxt[c];
        }
        if(node == -1) continue;
        // We consumed full s. Any j in pal_suf_ids gives a palindrome when appending word j
        for(int j : trie[node].pal_suf_ids){
            if(j == idx) continue;
            answer = max(answer, m + (int)words[j].size());
        }
    }

    cout << answer << "\n";
    return 0;
}