/* 最长回文拼接 - 哈希表+回文前缀检查 */
#include <bits/stdc++.h>
using namespace std;

// 检查字符串是否为回文
bool isPalindrome(const string &s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> strs(n);
    unordered_map<string, int> str_map;  // 存储字符串及其出现次数（本题中保证互不相同）

    for (int i = 0; i < n; ++i) {
        cin >> strs[i];
        str_map[strs[i]] = i;
    }

    int max_len = 0;
    for (int i = 0; i < n; ++i) {
        string s = strs[i];
        string rev_s(s.rbegin(), s.rend());
        
        // 情况1：直接找到反转字符串
        if (str_map.count(rev_s) && str_map[rev_s] != i) {
            max_len = max(max_len, 2 * (int)s.length());
        }
        
        // 情况2：检查s的各个前缀是否为回文，并找剩余部分的反转
        for (int k = 1; k < (int)s.length(); ++k) {
            if (isPalindrome(s.substr(0, k))) {
                string need = rev_s.substr(0, s.length() - k);
                if (str_map.count(need) && str_map[need] != i) {
                    max_len = max(max_len, (int)s.length() + (int)need.length());
                }
            }
        }
        
        // 情况3：检查s的各个后缀是否为回文，并找剩余部分的反转
        // 现在处理s作为第二个拼接部分的情况
        for (int k = 1; k < (int)s.length(); ++k) {
            if (isPalindrome(s.substr(k))) {
                string need = rev_s.substr(s.length() - k);
                if (str_map.count(need) && str_map[need] != i) {
                    max_len = max(max_len, (int)s.length() + (int)need.length());
                }
            }
        }
    }

    cout << max_len << '\n';
    return 0;
}