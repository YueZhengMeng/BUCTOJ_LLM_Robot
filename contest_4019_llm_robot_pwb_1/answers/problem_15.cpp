/* 文件头注释：使用埃拉托斯特尼筛法找出0～N内的所有素数 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    // 创建一个布尔数组，初始化为true，表示所有数都是素数
    vector<bool> isPrime(N + 1, true);
    
    // 0和1不是素数
    isPrime[0] = isPrime[1] = false;
    
    // 埃拉托斯特尼筛法
    for (int i = 2; i * i <= N; ++i) {
        if (isPrime[i]) {
            // 将i的倍数标记为非素数
            for (int j = i * i; j <= N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    // 输出所有素数
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) {
            cout << i << endl;
        }
    }
    
    return 0;
}