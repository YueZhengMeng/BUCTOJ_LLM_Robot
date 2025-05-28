/* 文件头注释：计算学生成绩的平均分及不及格人数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n; // 输入学生人数
    vector<int> scores(n); // 存储学生成绩
    int sum = 0; // 总分
    int failCount = 0; // 不及格人数
    vector<int> failScores; // 不及格成绩

    // 输入成绩并计算总分及不及格人数
    for (int i = 0; i < n; ++i) {
        cin >> scores[i];
        sum += scores[i];
        if (scores[i] < 60) {
            failCount++;
            failScores.push_back(scores[i]);
        }
    }

    // 输出平均分，保留1位小数
    cout << fixed << setprecision(1) << (double)sum / n << endl;

    // 输出不及格人数
    cout << failCount << endl;

    // 输出不及格成绩，最后一个后面没有空格
    if (failCount > 0) {
        for (int i = 0; i < failScores.size(); ++i) {
            if (i > 0) cout << " ";
            cout << failScores[i];
        }
        cout << endl;
    }

    return 0;
}