/* 文件头注释：核心算法为哈希集合交集检查，关键技术为哈希集合和集合列表的维护 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    // 为每个元素维护一个集合列表，记录它所属的集合编号
    unordered_map<int, unordered_set<int>> elementToSets;
    for (int k = 1; k <= N; ++k) {
        int Ci;
        cin >> Ci;
        for (int i = 0; i < Ci; ++i) {
            int element;
            cin >> element;
            elementToSets[element].insert(k);
        }
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int i, j;
        cin >> i >> j;
        // 检查两个元素的集合列表是否有交集
        bool found = false;
        for (int setID : elementToSets[i]) {
            if (elementToSets[j].count(setID)) {
                found = true;
                break;
            }
        }
        cout << (found ? "Yes" : "No") << endl;
    }

    return 0;
}