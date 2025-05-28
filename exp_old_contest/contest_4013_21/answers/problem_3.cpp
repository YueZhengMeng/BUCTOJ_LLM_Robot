/* 文件头注释：计算最大曼哈顿距离 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    int x_min = 6, x_max = 0, y_min = n + 1, y_max = 0;
    
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        x_min = min(x_min, x);
        x_max = max(x_max, x);
        y_min = min(y_min, y);
        y_max = max(y_max, y);
    }
    
    int max_distance = abs(x_max - x_min) + abs(y_max - y_min);
    cout << max_distance << endl;
    
    return 0;
}