#include <iostream>
#include <vector>
#include <algorithm> // For std::max

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // 读取测试用例数量
    while (T--) {
        int N, V;
        std::cin >> N >> V; // 读取骨头数量和背包体积

        std::vector<int> values(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> values[i]; // 读取每根骨头的价值
        }

        std::vector<int> volumes(N);
        for (int i = 0; i < N; ++i) {
            std::cin >> volumes[i]; // 读取每根骨头的体积
        }

        // dp[j] 表示背包容量为 j 时可以获得的最大价值
        std::vector<int> dp(V + 1, 0);

        // 遍历每根骨头
        for (int i = 0; i < N; ++i) {
            int current_value = values[i];
            int current_volume = volumes[i];
            // 从后向前遍历背包容量，确保每个物品只用一次
            for (int j = V; j >= current_volume; --j) {
                dp[j] = std::max(dp[j], dp[j - current_volume] + current_value);
            }
        }
        std::cout << dp[V] << std::endl; // 输出最大价值
    }
    return 0;
}