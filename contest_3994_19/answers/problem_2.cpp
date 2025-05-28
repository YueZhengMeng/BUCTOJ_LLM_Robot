/* 
  代码头注释： 
  问题 C: 分巧克力 
  算法：枚举四种拆分模式（HH, HV, VH, VV），
       利用凸性只在交点附近取样实现 O(1) 优化。
  关键技巧：线性函数求最小最大值，折线相交点 2/3 处取整。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

// 计算“横后纵”或“纵后横”混合拆分时的最大差值
// h: 第一段长度（行数或列数）， 
// N: 主方向总长度， M: 另一方向总长度
// c1 = floor(M/2), c2 = ceil(M/2)
inline ll mixed_diff(ll h, ll N, ll M, ll c1, ll c2) {
    // DEBUG: 计算两条线性函数值
    ll part1 = h * c2 - (N - h) * M;
    ll part2 = (N - h) * M - h * c1;
    // 最大差即两者中的较大者
    return max(part1, part2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    // 情况 HH：3 条水平条带
    // 切成 (x, x, n-2x) 行高，最优时差 0 或 1 行
    ll ansHH = (n % 3 == 0 ? 0LL : 1LL) * m;

    // 情况 VV：3 条垂直条带
    ll ansVV = (m % 3 == 0 ? 0LL : 1LL) * n;

    // 情况 HV：先横切 h 行，再对 h×m 区域纵切
    ll c1_m = m / 2;               // floor(m/2)
    ll c2_m = (m + 1) / 2;         // ceil(m/2)
    // 交点 h ≈ 2n/3
    ll h0 = (2 * n) / 3;
    ll ansHV = LLONG_MAX;
    for (ll dh = 0; dh <= 1; ++dh) {
        ll h = h0 + dh;
        if (h >= 1 && h < n) {
            // DEBUG: 只在 h0 和 h0+1 处取样
            ansHV = min(ansHV, mixed_diff(h, n, m, c1_m, c2_m));
        }
    }

    // 情况 VH：先纵切 w 列，再对 n×w 区域横切
    ll c1_n = n / 2;               // floor(n/2)
    ll c2_n = (n + 1) / 2;         // ceil(n/2)
    ll w0 = (2 * m) / 3;
    ll ansVH = LLONG_MAX;
    for (ll dw = 0; dw <= 1; ++dw) {
        ll w = w0 + dw;
        if (w >= 1 && w < m) {
            ansVH = min(ansVH, mixed_diff(w, m, n, c1_n, c2_n));
        }
    }

    // 最终答案
    ll answer = min( min(ansHH, ansVV), min(ansHV, ansVH) );
    cout << answer << "\n";
    return 0;
}

/*
时间复杂度：O(1)，只做常数级运算和小范围枚举  
空间复杂度：O(1)，仅使用固定数量的标量变量
*/