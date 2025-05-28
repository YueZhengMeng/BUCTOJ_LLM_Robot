/* 代码头注释：扫描线算法计算矩形面积并集 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 0x3f3f3f3f;

struct Event {
    int x, y1, y2, type; // type: 1 for start, -1 for end
    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Event> events;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        events.push_back({x1, y1, y2, 1});
        events.push_back({x2, y1, y2, -1});
    }

    sort(events.begin(), events.end());

    multiset<pair<int, int>> active; // {y1, y2}
    ll area = 0;
    int prev_x = events[0].x;

    for (const auto& event : events) {
        int x = event.x;
        int y1 = event.y1;
        int y2 = event.y2;
        int type = event.type;

        if (!active.empty()) {
            int total_height = 0;
            int prev_y = -1;
            for (const auto& seg : active) {
                if (seg.first > prev_y) {
                    total_height += seg.second - seg.first;
                } else if (seg.second > prev_y) {
                    total_height += seg.second - prev_y;
                }
                prev_y = max(prev_y, seg.second);
            }
            area += (ll)total_height * (x - prev_x);
        }

        if (type == 1) {
            active.insert({y1, y2});
        } else {
            active.erase(active.find({y1, y2}));
        }

        prev_x = x;
    }

    cout << area << endl;

    return 0;
}