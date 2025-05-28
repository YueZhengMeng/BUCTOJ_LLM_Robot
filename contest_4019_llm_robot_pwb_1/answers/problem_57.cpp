/* 文件头注释：第二价格竞拍问题，通过遍历数组找到最大值和次大值 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T; // 读取竞拍组数
    while (T--) {
        int N;
        cin >> N; // 读取投标人数量
        vector<int> bids(N);
        for (int i = 0; i < N; ++i) {
            cin >> bids[i]; // 读取每个投标人的投标价
        }
        
        int maxBid = 0, secondMaxBid = 0;
        int winnerIndex = 0;
        
        // 遍历数组找到最大值和次大值
        for (int i = 0; i < N; ++i) {
            if (bids[i] > maxBid) {
                secondMaxBid = maxBid;
                maxBid = bids[i];
                winnerIndex = i;
            } else if (bids[i] > secondMaxBid) {
                secondMaxBid = bids[i];
            }
        }
        
        // 输出赢家和他需要支付的费用
        cout << winnerIndex + 1 << " " << secondMaxBid << endl;
    }
    return 0;
}