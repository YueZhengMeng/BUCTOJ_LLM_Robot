/* 
代码头注释：优化构造法寻找满足条件的B
关键技巧：字符串匹配 + 子串查找 + 候选构造
主要修改标记：[FIX] 说明修改原因
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// [FIX] 添加辅助函数，用于手动实现字符串到整数的转换
ll stringToLong(const string& s) {
    ll res = 0;
    for (char c : s) {
        res = res * 10 + (c - '0');
    }
    return res;
}

// [FIX] 添加辅助函数，用于在 A 的任意位置插入单个数字
vector<string> insertDigits(const string& A) {
    vector<string> candidates;
    // 尝试将 A 插入到不同的位置形成候选 B
    for (int i = 0; i <= A.size(); ++i) {
        string prefix = (i > 0) ? A.substr(0, i) : ""; // [FIX] 明确处理边界情况
        string suffix = (i < A.size()) ? A.substr(i) : ""; // [FIX] 明确处理边界情况
        for (int j = 0; j <= 9; ++j) { // 在 A 的前后插入数字 0-9
            string candidate = prefix + to_string(j) + suffix;
            candidates.push_back(candidate);
        }
    }
    return candidates;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A_str; // 输入的数字字符串
    int A_int;
    cin >> A_int;
    A_str = to_string(A_int);

    constexpr int MAX_B = (1 << 31) - 1; // B的上界

    // [FIX] 优先检查 A 是否满足条件
    ll A_val = stringToLong(A_str); // [FIX] 替换 stoll
    if (A_val > 0 && A_val <= MAX_B) {
        string Bx2_str = to_string(2LL * A_val); // 计算 A×2 的字符串形式
        if (Bx2_str.find(A_str) != string::npos) { // 检查 A 是否是 A×2 的子串
            cout << A_val << '\n'; // 输出 A 本身作为解
            return 0;
        }
    }

    // [FIX] 使用改进的生成候选方法替代暴力枚举
    vector<string> candidates = insertDigits(A_str);

    for (const string& B_str : candidates) {
        ll B = stringToLong(B_str); // [FIX] 替换 stoll
        if (B > MAX_B || B == 0) continue; // [FIX] 确保 B 在范围内

        string Bx2_str = to_string(2LL * B); // 计算 B×2 的字符串形式

        // 检查 A 是否是 B 和 B×2 的子串
        if (B_str.find(A_str) != string::npos && Bx2_str.find(A_str) != string::npos) {
            cout << B << '\n'; // 输出找到的 B
            return 0;
        }
    }

    // 根据题目保证，至少存在一个解，因此不会到达此处
    return 0;
}