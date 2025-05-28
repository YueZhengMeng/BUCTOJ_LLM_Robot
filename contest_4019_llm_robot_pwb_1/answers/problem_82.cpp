/* 文件头注释：KMP字符串匹配算法，计算模式串的所有出现位置及其前缀的最长border长度 */
#include <bits/stdc++.h>
using namespace std;

// 构建KMP算法的next数组
vector<int> buildNext(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);
    for (int i = 1, j = 0; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

// KMP算法，返回所有匹配位置的起始索引
vector<int> kmpSearch(const string& text, const string& pattern, const vector<int>& next) {
    vector<int> positions;
    int n = text.length(), m = pattern.length();
    for (int i = 0, j = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            positions.push_back(i - m + 1);
            j = next[j - 1];
        }
    }
    return positions;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    
    // 构建next数组
    vector<int> next = buildNext(s2);
    
    // 使用KMP算法查找所有匹配位置
    vector<int> positions = kmpSearch(s1, s2, next);
    
    // 输出所有匹配位置
    for (int pos : positions) {
        cout << pos + 1 << endl; // 转换为1-based索引
    }
    
    // 输出每个前缀的最长border长度
    for (int i = 0; i < s2.length(); ++i) {
        cout << next[i] << " ";
    }
    cout << endl;
    
    return 0;
}