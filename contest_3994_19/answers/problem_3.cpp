/* 
 Algorithm: 分段主项 + 小规模枚举 + 微调 
 核心技巧：枚举 e^3(A3) 与 e^4(A4) 的使用次数，确保总表达式长度≤20，再贪心凑余数。
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;

    // 预定义主元及其 floor 值和表达式
    constexpr int A3 = 20;      // floor(e*e*e)
    const string S3 = "e*e*e";  // 长度 5
    constexpr int A4 = 54;      // floor(e*e*e*e)
    const string S4 = "e*e*e*e";// 长度 7

    string answer;
    bool found = false;

    // 枚举 k4 次数（0~1次）和 k3 次数（0~3次）
    for (int k4 = 0; k4 <= 1 && !found; k4++){
        for (int k3 = 0; k3 <= 3 && !found; k3++){
            int mainSum = k4 * A4 + k3 * A3;
            if (mainSum > x) continue;
            int r = x - mainSum;

            // 构造主项字符串
            string mainStr;
            // 先加 k4 次 S4
            for (int i = 0; i < k4; i++){
                if (!mainStr.empty()) mainStr += '+';
                mainStr += S4;
            }
            // 接着加 k3 次 S3
            for (int i = 0; i < k3; i++){
                if (!mainStr.empty()) mainStr += '+';
                mainStr += S3;
            }

            int lenMain = (int)mainStr.size();
            if (lenMain > 20) continue; // 剪枝

            // 贪心凑余 r（3->2->1），生成 adjStr
            string adjStr;
            int rem = r;
            // 尽可能多用 p (floor=3)
            int cnt3 = rem / 3;
            rem -= cnt3 * 3;
            for (int i = 0; i < cnt3; i++){
                adjStr += "+p";
            }
            // 再用 e (floor=2)
            int cnt2 = rem / 2;
            rem -= cnt2 * 2;
            for (int i = 0; i < cnt2; i++){
                adjStr += "+e";
            }
            // 剩下 0 或 1，1 用 e*(p-e)
            if (rem == 1){
                adjStr += "+e*(p-e)";
            }
            //  rem==0 则不加

            // 计算总长度，注意可能去掉 leading '+'
            int totalLen = lenMain;
            if (!adjStr.empty()){
                totalLen += (int)adjStr.size();
            }

            if (totalLen > 20) continue; // 太长则跳过

            // 组合答案
            if (mainStr.empty()){
                // 全靠 adj
                if (adjStr.empty()){
                    // x=0 不存在，但保护
                    answer = "e";
                } else {
                    // 去掉首位 '+'
                    answer = adjStr[0] == '+' ? adjStr.substr(1) : adjStr;
                }
            } else {
                // main + adj
                answer = mainStr + adjStr;
            }

            // 找到合法解后退出
            found = true;
        }
    }

    // 理论上总能找到，直接输出
    cout << answer << "\n";
    return 0;
}