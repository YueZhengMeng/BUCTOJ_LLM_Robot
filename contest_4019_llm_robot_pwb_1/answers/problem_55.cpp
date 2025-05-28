/* 文件头注释：字符串的输入输出处理 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore(); // 忽略第一行后的换行符

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    // 输出前N行
    for (int i = 0; i < N && i < lines.size(); ++i) {
        cout << lines[i] << endl;
    }

    // 输出剩余行，按空格或回车分割
    for (int i = N; i < lines.size(); ++i) {
        stringstream ss(lines[i]);
        string word;
        while (ss >> word) {
            cout << word << endl;
        }
    }

    return 0;
}