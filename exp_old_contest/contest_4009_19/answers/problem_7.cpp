/* 
  Kitchen Scheduling with Minimum Chefs
  - Parallel machine scheduling
  - Feasibility check via bucket-queue optimization
  - Binary search for minimum m with sum/K 下界剪枝
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll K;
vector<ll> a;
ll sumA;
ll mx;
int Kint;
vector<int> cnt;

// Check if we can schedule all N tasks within time K using m chefs
bool canFinishWith(int m) {
    // 下界保护：总工作量超出 m·K，直接失败
    if (sumA > (ll)m * K) return false;  // [FIX] 提前剪枝，避免无效模拟

    // 用桶队列记录空闲时间
    fill(cnt.begin(), cnt.end(), 0);
    cnt[0] = m;
    int cur = 0;  // 当前最小有空闲厨师的时间

    for (int i = 0; i < N; i++) {
        // 找到下一个有空闲厨师的时间 cur
        while (cur <= Kint && cnt[cur] == 0) cur++;
        if (cur > Kint) return false;  // 无可用厨师

        // 分配一位厨师在 cur 开始做第 i 道菜
        cnt[cur]--;
        ll finish = (ll)cur + a[i];
        if (finish > K) return false;  // 超时

        // 该厨师 finish 时刻再次空闲
        cnt[(int)finish]++;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    a.resize(N);
    sumA = 0; mx = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        sumA += a[i];
        mx = max(mx, a[i]);
    }

    // 单道菜超出 K，必定无法完成
    if (mx > K) {
        cout << -1 << "\n";
        return 0;
    }

    // 准备桶队列容量
    Kint = (int)K;
    cnt.assign(Kint + 1, 0);

    // 下界剪枝：sumA <= m*K => m >= ceil(sumA/K)
    ll m_min = (sumA + K - 1) / K;
    int lo = (int)max(1LL, m_min);
    if (lo > N) {
        cout << -1 << "\n";
        return 0;
    }
    int hi = N, ans = N + 1;

    // 二分最少厨师数
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (canFinishWith(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (ans == N + 1) ans = -1;
    cout << ans << "\n";
    return 0;
}