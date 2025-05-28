/* 文件头注释：完数查找与因子输出 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N; // 输入N

    for (int num = 2; num <= N; ++num) { // 遍历1到N的所有数
        int sum = 1; // 因子和，初始为1（因为1是所有数的因子）
        vector<int> factors = {1}; // 存储因子，初始包含1

        for (int i = 2; i * i <= num; ++i) { // 计算因子
            if (num % i == 0) {
                sum += i;
                factors.push_back(i);
                if (i != num / i) { // 避免重复添加平方数因子
                    sum += num / i;
                    factors.push_back(num / i);
                }
            }
        }

        if (sum == num) { // 如果因子和等于该数，输出完数及其因子
            cout << num << " its factors are ";
            sort(factors.begin(), factors.end()); // 因子按升序排序
            for (int factor : factors) {
                cout << factor << " ";
            }
            cout << endl;
        }
    }

    return 0;
}