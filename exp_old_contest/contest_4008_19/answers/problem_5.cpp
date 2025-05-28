/* 
   Lagrangian relaxation + binary search on penalty λ.
   For each λ, compute best_gain_i = max(b_i, a_i+λ), pick top k = s+t,
   count how many from A-side.  Binary-search λ so that count_A = s,
   then adjust minor over-count by dropping smallest diffs.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, t;
    cin >> n >> s >> t;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    int k = s + t;

    // eval(λ): 返回在当前 λ 下，选前 k 个时 A 侧（diff>0）的数量
    auto eval = [&](int lam){
        static vector<pair<int,int>> V;
        V.clear();
        V.reserve(n);
        for(int i = 0; i < n; i++){
            int diff = (a[i] - b[i]) + lam;    // gainA - gainB
            int best_gain = b[i] + max(diff, 0);
            V.emplace_back(best_gain, diff);
        }
        // [FIX] 比较时先按 best_gain，再按 diff 保证平局时一致性（优先保留 A 侧）
        nth_element(V.begin(), V.begin() + k, V.end(),
            [](const pair<int,int>& L, const pair<int,int>& R){
                if(L.first != R.first) return L.first > R.first;
                return L.second > R.second;
            });
        int cntA = 0;
        for(int i = 0; i < k; i++){
            if (V[i].second > 0) cntA++;
        }
        return cntA;
    };

    // 二分找到最小的 lam 使得 eval(lam) >= s
    int lo = -5000, hi = 5000;
    while(lo < hi){
        int mid = lo + ((hi - lo) >> 1);
        if (eval(mid) >= s) hi = mid;
        else lo = mid + 1;
    }
    int lam = lo;

    // 最终在 lam 下选前 k 个，并累计得分 & diff
    vector<pair<int,int>> V;
    V.reserve(n);
    for(int i = 0; i < n; i++){
        int diff = (a[i] - b[i]) + lam;
        int best_gain = b[i] + max(diff, 0);
        V.emplace_back(best_gain, diff);
    }
    // [FIX] 同上，保持 sort 的平局破除与 nth_element 一致
    sort(V.begin(), V.end(),
         [](const pair<int,int>& L, const pair<int,int>& R){
             if(L.first != R.first) return L.first > R.first;
             return L.second > R.second;
         });

    ll sum_gain = 0;
    vector<int> posDiff;
    posDiff.reserve(k);
    for(int i = 0; i < k; i++){
        sum_gain += V[i].first;
        if (V[i].second > 0)
            posDiff.push_back(V[i].second);
    }

    int cntA = (int)posDiff.size();
    int extra = cntA - s; // 多余的 A 侧数
    ll sum_remove = 0;
    if (extra > 0) {
        sort(posDiff.begin(), posDiff.end());
        for(int i = 0; i < extra; i++)
            sum_remove += posDiff[i];
    }

    // 最终答案去掉 λ*s 的 bias，并减去多余的那部分 diff
    ll answer = sum_gain - sum_remove - ll(lam) * ll(s);
    cout << answer << "\n";
    return 0;
}