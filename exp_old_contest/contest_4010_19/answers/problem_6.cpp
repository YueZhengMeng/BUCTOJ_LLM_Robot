/* 
   Algorithm: Best‐first search (min‐heap) over a layered DAG.
   Each state is a strictly‐increasing prefix ending at (row, col) with accumulated sum.
   We push all row1 cells, then always pop the smallest‐sum prefix, count it,
   and generate its children in the next row (where next_value > current_value).
   Stop when we've popped k prefixes.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct State {
    ll sum;
    int row, col;
    // Compare by sum for min-heap
    bool operator>(State const &o) const {
        return sum > o.sum;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> grid(N+1, vector<int>(M));
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < M; j++){
            cin >> grid[i][j];
        }
    }

    // For each row, prepare a sorted list of (value, colIndex)
    vector<vector<pair<int,int>>> sortedRow(N+2);
    for(int i = 1; i <= N; i++){
        sortedRow[i].reserve(M);
        for(int j = 0; j < M; j++){
            sortedRow[i].emplace_back(grid[i][j], j);
        }
        sort(sortedRow[i].begin(), sortedRow[i].end());
    }

    // Min-heap of states
    priority_queue<State, vector<State>, greater<State>> pq;
    // Push all row-1 prefixes (length = 1)
    for(int j = 0; j < M; j++){
        pq.push({ (ll)grid[1][j], 1, j });
    }

    // Extract k times
    int count = 0;
    while(!pq.empty()){
        State cur = pq.top(); 
        pq.pop();
        count++;
        if(count == K){
            cout << cur.sum << "\n";
            return 0;
        }
        // Generate successors in row = cur.row + 1
        if(cur.row < N){
            int rnx = cur.row + 1;
            int vcur = grid[cur.row][cur.col];
            // In sortedRow[rnx], find first whose value > vcur
            auto &vec = sortedRow[rnx];
            auto it = upper_bound(vec.begin(), vec.end(),
                                  make_pair(vcur, M+1));
            // Push all successors
            for(; it != vec.end(); ++it){
                ll newSum = cur.sum + (ll)it->first;
                pq.push({ newSum, rnx, it->second });
            }
        }
    }
    return 0;
}