/* 文件头注释：计算学生成绩的平均值和最高分学生 */
#include <bits/stdc++.h>
using namespace std;

struct Student {
    string id;
    string name;
    int score1, score2, score3;
    int total() const {
        return score1 + score2 + score3;
    }
};

int main() {
    int N;
    cin >> N;
    if (N == 0) {
        cout << "0 0 0\n";
        return 0;
    }

    vector<Student> students(N);
    int sum1 = 0, sum2 = 0, sum3 = 0;
    int maxTotal = -1;
    int maxIndex = 0;

    for (int i = 0; i < N; ++i) {
        cin >> students[i].id >> students[i].name >> students[i].score1 >> students[i].score2 >> students[i].score3;
        sum1 += students[i].score1;
        sum2 += students[i].score2;
        sum3 += students[i].score3;
        if (students[i].total() > maxTotal) {
            maxTotal = students[i].total();
            maxIndex = i;
        }
    }

    // 计算平均成绩并舍弃小数
    int avg1 = sum1 / N;
    int avg2 = sum2 / N;
    int avg3 = sum3 / N;

    cout << avg1 << " " << avg2 << " " << avg3 << "\n";
    cout << students[maxIndex].id << " " << students[maxIndex].name << " "
         << students[maxIndex].score1 << " " << students[maxIndex].score2 << " "
         << students[maxIndex].score3 << "\n";

    return 0;
}