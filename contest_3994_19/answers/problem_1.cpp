/* 
 算法名称： 枚举高位拼接 + 字符串查找
 关键技巧： 将 A 放在 B 的任意位置（前缀/后缀），枚举 x，双向子串检测
 时间复杂度： O(K)，K≈10^6
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;
constexpr int MAX_X = 100000;         // x 枚举上限

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if(!(cin >> s)) return 0;
    int len = (int)s.size();
    // 预计算 10^0..10
    vector<ll> p10(11, 1);
    for(int i = 1; i <= 10; i++){
        p10[i] = p10[i-1] * 10LL;
    }
    ll powA = p10[len];
    // 将 A 转为整数
    int a = stoi(s);

    // [FIX] 1. 前缀枚举：B = A * 10^k + x，使 A 位于高位
    for(int k = 1; k <= 10; k++){
        ll base = ll(a) * p10[k];
        if(base > INT_MAX) break;       // 超出 int 范围，停止更高 k
        for(int x = 0; x <= MAX_X; x++){
            ll B = base + x;
            if(B > INT_MAX) break;
            string Bs = to_string(B);
            if(Bs.find(s) == string::npos) continue;
            ll TB = B << 1;             // 2*B
            string TBs = to_string(TB);
            if(TBs.find(s) != string::npos){
                cout << B;
                return 0;
            }
        }
    }

    // [FIX] 2. 原后缀枚举：B = x*10^len + A，保证 A 位于低位
    for(int x = 0; x <= MAX_X; x++){
        ll B = ll(x) * powA + a;
        if(B > INT_MAX) break;           // 超出 int 范围，停止枚举
        // 此处 B 字符串必定含 s（后缀），只需检测 2B
        ll TB = B << 1;                  // 2*B
        string TBs = to_string(TB);
        if(TBs.find(s) != string::npos){
            cout << B;
            return 0;
        }
    }

    // 按题意保证至少有解，此处理论不会到达
    return 0;
}