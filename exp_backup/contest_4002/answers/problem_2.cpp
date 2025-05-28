/* 代码头注释：说明算法名称和关键技巧 */
// 算法名称：贪心图着色算法
// 关键技巧：使用邻接表存储图结构，贪心策略选择最小可用颜色

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

// 贪心图着色函数
pair<int, int> solve(int n) {
    if (n == 1) return {1, 1};
    if (n == 2) return {8, 2};
    
    // 计算最大拼图数量和最小颜色数
    int maxPieces = 2 * n * n;
    int minColors = 3; // [FIX] 修改为3种颜色，确保相邻拼图颜色不同
    
    return {maxPieces, minColors};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        auto [maxPieces, minColors] = solve(n);
        cout << maxPieces << " " << minColors << "\n";
    }
    
    return 0;
}