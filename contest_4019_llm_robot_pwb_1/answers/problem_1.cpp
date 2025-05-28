/* 文件头注释：字符替换加密算法 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    // 定义并初始化字符变量
    char c1 = 'C', c2 = 'h', c3 = 'i', c4 = 'n', c5 = 'a';
    
    // 对每个字符进行加密，即将其ASCII值加4
    c1 += 4;
    c2 += 4;
    c3 += 4;
    c4 += 4;
    c5 += 4;
    
    // 输出加密后的结果
    cout << c1 << c2 << c3 << c4 << c5 << endl;
    
    return 0;
}