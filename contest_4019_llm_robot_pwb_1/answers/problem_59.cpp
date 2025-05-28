/* 文件头注释：使用自定义排序规则筛选符合条件的钢管 */
#include <bits/stdc++.h>
using namespace std;

struct SteelPipe {
    int length;
    int diameter;
    int code;
};

// 自定义比较函数
bool compare(const SteelPipe &a, const SteelPipe &b) {
    if (a.length != b.length) {
        return a.length > b.length; // 长度降序
    } else if (a.diameter != b.diameter) {
        return a.diameter < b.diameter; // 直径升序
    } else {
        return a.code > b.code; // 编码降序
    }
}

int main() {
    int T;
    cin >> T;
    vector<SteelPipe> pipes(T);
    
    // 读取钢管信息
    for (int i = 0; i < T; ++i) {
        cin >> pipes[i].length >> pipes[i].diameter >> pipes[i].code;
    }
    
    // 按自定义规则排序
    sort(pipes.begin(), pipes.end(), compare);
    
    // 输出符合条件钢管的编码
    cout << pipes[0].code << endl;
    
    return 0;
}