/* 
  算法名称：经典博弈期望贪心
  关键技巧：线性期望+边际概率(2/5,2/5,1/5)化简为整数比较
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int K = 3;  // 盒子个数常量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;  // 防御性读入
    // 处理所有轮次
    for (int i = 0; i < n; i++) {
        int v[K];
        cin >> v[0] >> v[1] >> v[2];
        // 排序：升序 v[0]=z, v[1]=y, v[2]=x
        sort(v, v + K);
        int z = v[0], y = v[1], x = v[2];
        // [FIX] 计算三种选择的“期望差值*5”值，以 Alice 得分减去 Bob 得分为目标
        // 选 x 时 E*5 = 3*x - 2*y - z
        int ex5 = 3 * x - 2 * y - z;
        // 选 y 时 E*5 = 3*y - 2*x - z
        int ey5 = 3 * y - 2 * x - z;
        // 选 z 时 E*5 = 4*z - 2*y - 2*x
        int ez5 = 4 * z - 2 * y - 2 * x;

        // 比较三者，取最大
        int best = ex5;
        int answer = x;
        if (ey5 > best) {
            best = ey5;
            answer = y;
        }
        if (ez5 > best) {
            best = ez5;
            answer = z;
        }
        // 输出该轮Alice应选的盒子数值
        cout << answer << '\n';
    }

    return 0;
}
/*
 时间复杂度：O(n)；每轮排序固定3元素O(1)，常数次算术比较
 空间复杂度：O(1)额外（原地3元素数组）
 关键优化点：化浮点为整数比较，省去double带来的精度或性能开销
*/