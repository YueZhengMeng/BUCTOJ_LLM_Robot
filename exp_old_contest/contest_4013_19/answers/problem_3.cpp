/* 
  Algorithm: Maximum Manhattan distance via transformed extrema
  Key idea: max_{i,j} |x_i - x_j| + |y_i - y_j| 
           = max( (x+y)_max - (x+y)_min, (x-y)_max - (x-y)_min ) 
*/
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;
    cin >> n >> m;

    // Initialize extrema for s1 = x+y and s2 = x-y
    int minS1 = INT_MAX, maxS1 = INT_MIN;
    int minS2 = INT_MAX, maxS2 = INT_MIN;

    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        int s1 = x + y;
        int s2 = x - y;
        if(s1 < minS1) minS1 = s1;
        if(s1 > maxS1) maxS1 = s1;
        if(s2 < minS2) minS2 = s2;
        if(s2 > maxS2) maxS2 = s2;
    }

    int ans = max(maxS1 - minS1, maxS2 - minS2);
    cout << ans << "\n";
    return 0;
}