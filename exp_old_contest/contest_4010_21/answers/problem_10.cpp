/* 文件头注释：说明核心算法名称和关键技术 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 500010;

vector<int> tree[MAXN];
int a[MAXN];
int lcm[MAXN];

// 计算最小公倍数
long long computeLCM(long long a, long long b) {
    return a / __gcd(a, b) * b;
}

// DFS遍历树，计算每个子树的最小过载周期
void dfs(int u) {
    lcm[u] = a[u];
    for (int v : tree[u]) {
        dfs(v);
        lcm[u] = computeLCM(lcm[u], lcm[v]) % MOD;
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 2; i <= n; ++i) {
        int parent;
        scanf("%d", &parent);
        tree[parent].push_back(i);
    }

    // 预处理每个子树的最小过载周期
    dfs(1);

    int lastans = 0;
    while (q--) {
        int x;
        scanf("%d", &x);
        int u = (x + lastans) % n + 1;
        lastans = lcm[u];
        printf("%d\n", lastans);
    }

    return 0;
}