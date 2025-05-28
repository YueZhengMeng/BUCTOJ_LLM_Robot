#include <iostream>
#include <vector>
#include <numeric> // 通常包含了有用的函数，如此处非必须

int main() {
    // 优化C++标准流的输入输出速度
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // dp[i] 表示爬 i 级台阶的方法数。
    // M 的范围是 1 到 40, 所以 M-1 (需要爬的台阶数) 的范围是 0 到 39。
    // 我们需要一个大小为 40 的数组来存储 dp[0] 到 dp[39]。
    std::vector<long long> dp(40); // 使用 long long 以防数字过大，尽管此题int也够

    // 基本情况
    // dp[0] 对应 M=1, 需要爬 0 级台阶
    dp[0] = 1; 
    // dp[1] 对应 M=2, 需要爬 1 级台阶
    // 确保数组大小至少为2才设置dp[1], 此处dp大小为40, 所以总是安全的
    if (40 > 1) { // 实际上这个判断对于固定大小40的vector是不必要的，但保留逻辑清晰性
        dp[1] = 1;
    }

    // 递推计算 dp[2] 到 dp[39]
    // i 表示要爬的台阶数
    for (int i = 2; i < 40; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    int N; // 测试实例的个数
    std::cin >> N;
    while (N--) {
        int M; // 楼梯级数
        std::cin >> M;
        // 需要爬 M-1 级台阶
        std::cout << dp[M-1] << "\n"; // 使用 "\n" 通常比 std::endl 效率稍高
    }

    return 0;
}