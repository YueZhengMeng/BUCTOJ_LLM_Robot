/* 文件头注释：动态规划算法，模拟手指在键盘上的移动 */
#include <bits/stdc++.h>
using namespace std;

// 定义键盘上每个键的相邻键
const vector<vector<char>> adjacent = {
    {'q', 'w'}, {'w', 'e', 'q'}, {'e', 'r', 'w'}, {'r', 't', 'e'}, {'t', 'y', 'r'}, {'y', 'u', 't'}, {'u', 'i', 'y'}, {'i', 'o', 'u'}, {'o', 'p', 'i'}, {'p', 'o'},
    {'a', 's'}, {'s', 'd', 'a'}, {'d', 'f', 's'}, {'f', 'g', 'd', 'r'}, {'g', 'h', 'f', 't'}, {'h', 'j', 'g', 'y'}, {'j', 'k', 'h', 'u'}, {'k', 'l', 'j', 'i'}, {'l', 'k', 'o'}, {';', 'l', 'p'},
    {'z', 'x'}, {'x', 'c', 'z'}, {'c', 'v', 'x'}, {'v', 'b', 'c', 'f'}, {'b', 'n', 'v', 'g'}, {'n', 'm', 'b', 'h'}, {'m', 'n', 'j'}, {',', 'm', 'k'}, {'.', ',', 'l'}, {'/', '.', ';'}
};

// 获取字符在键盘上的索引
int getIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

// 判断两个键是否相邻
bool isAdjacent(char a, char b) {
    int idx = getIndex(a);
    if (idx == -1) return false;
    for (char adj : adjacent[idx]) {
        if (adj == b) return true;
    }
    return false;
}

// 计算两个键之间的最短路径
int getDistance(char a, char b) {
    if (a == b) return 0;
    if (isAdjacent(a, b)) return 1;
    
    // 使用 BFS 计算最短路径
    queue<pair<char, int>> q;
    q.push({a, 0});
    unordered_set<char> visited;
    visited.insert(a);
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        char currentChar = current.first;
        int currentDist = current.second;
        
        int idx = getIndex(currentChar);
        if (idx == -1) continue;
        
        for (char adj : adjacent[idx]) {
            if (adj == b) {
                return currentDist + 1;
            }
            if (visited.find(adj) == visited.end()) {
                visited.insert(adj);
                q.push({adj, currentDist + 1});
            }
        }
    }
    
    return 2; // 如果未找到路径，返回2（理论上不会发生）
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        if (S.empty()) {
            cout << 0 << endl;
            continue;
        }
        char left = 'f', right = 'j';
        int time = 0;
        for (char c : S) {
            if (c == left || c == right) {
                // 如果目标键已经是当前手指的位置，不需要移动
                continue;
            }
            if (isAdjacent(left, c)) {
                left = c;
                time += 1;
            } else if (isAdjacent(right, c)) {
                right = c;
                time += 1;
            } else {
                // 如果目标键与两个手指都不相邻，选择移动距离较近的手指
                int leftDistance = getDistance(left, c);
                int rightDistance = getDistance(right, c);
                if (leftDistance <= rightDistance) {
                    left = c;
                    time += leftDistance;
                } else {
                    right = c;
                    time += rightDistance;
                }
            }
        }
        cout << time << endl;
    }
    return 0;
}