#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> weights(n);
    std::vector<int> values(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i] >> values[i];
    }

    int W;
    std::cin >> W;

    // dp[j] 将存储容量为 j 时可以获得的最大价值
    // 初始化为0，因为物品价值非负
    // W 最大为 10000，所以 W+1
    std::vector<long long> dp(W + 1, 0); // 使用 long long 以防万一，虽然此题 int 应该够用
                                         // 最大价值 v_i=100, W=10000, 若 w_i=1, 则 100*10000 = 1,000,000，在 int 范围内
                                         // 但使用 long long 是个好习惯

    // 遍历每种物品
    for (int i = 0; i < n; ++i) {
        int item_weight = weights[i];
        int item_value = values[i];
        
        // 对于当前物品，更新 dp 表
        // j 从 item_weight 开始，确保可以放入当前物品
        // j 必须正序遍历，以实现完全背包（物品可多次选取）
        for (int j = item_weight; j <= W; ++j) {
            dp[j] = std::max(dp[j], dp[j - item_weight] + item_value);
        }
    }

    std::cout << dp[W] << std::endl;

    return 0;
}