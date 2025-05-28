/* 代码头注释：扫描线算法计算矩形面积并 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

struct Event {
    int x1, x2, type; // type: 1 for bottom, -1 for top
    Event(int x1, int x2, int type) : x1(x1), x2(x2), type(type) {}
    bool operator<(const Event& other) const {
        return x1 < other.x1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, vector<Event>>> events;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({y1, {Event(x1, x2, 1)}});
        events.push_back({y2, {Event(x1, x2, -1)}});
    }

    // Sort events by y coordinate
    sort(events.begin(), events.end(), [](const pair<int, vector<Event>>& a, const pair<int, vector<Event>>& b) {
        return a.first < b.first;
    });

    multiset<Event> active;
    ll area = 0;
    int prev_y = 0;

    for (const auto& event : events) {
        int y = event.first;
        if (!active.empty()) {
            int height = y - prev_y;
            int total_width = 0;
            int prev_x = -1;
            for (const auto& e : active) {
                if (prev_x < e.x1) {
                    total_width += e.x2 - e.x1;
                    prev_x = e.x2;
                } else if (prev_x < e.x2) {
                    total_width += e.x2 - prev_x;
                    prev_x = e.x2;
                }
            }
            area += (ll)height * total_width;
        }
        for (const auto& e : event.second) {
            if (e.type == 1) {
                active.insert(e);
            } else {
                active.erase(active.find(e));
            }
        }
        prev_y = y;
    }

    cout << area << endl;
    return 0;
}