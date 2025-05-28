/* 文件头注释：学生信息输入输出处理 */
#include <bits/stdc++.h>
using namespace std;

// 定义学生结构体
struct Student {
    string id;
    string name;
    int score1, score2, score3;
};

// 输入一个学生的数据记录
void input(Student &student) {
    cin >> student.id >> student.name >> student.score1 >> student.score2 >> student.score3;
}

// 打印一个学生的数据记录
void print(const Student &student) {
    cout << student.id << "," << student.name << "," << student.score1 << "," << student.score2 << "," << student.score3 << endl;
}

int main() {
    int N;
    cin >> N; // 读取学生数量
    vector<Student> students(N); // 存储学生信息的数组

    // 输入每个学生的数据
    for (int i = 0; i < N; ++i) {
        input(students[i]);
    }

    // 输出每个学生的数据
    for (int i = 0; i < N; ++i) {
        print(students[i]);
    }

    return 0;
}