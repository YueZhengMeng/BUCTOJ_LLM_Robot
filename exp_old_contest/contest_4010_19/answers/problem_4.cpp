/* 
  Scheduling with tails (delivery times) 
  Optimal: sort jobs by descending b_i.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int,int>> jobs(n);
    for(int i = 0; i < n; i++){
        cin >> jobs[i].first >> jobs[i].second; // (a_i, b_i)
    }

    // Sort by descending b_i (the consumption time)
    sort(jobs.begin(), jobs.end(), [](const pair<int,int>& A, const pair<int,int>& B){
        return A.second > B.second;
    });

    ll productionTime = 0;   // cumulative a_i
    ll result = 0;           // max(productionTime + b_i)
    for(auto &job : jobs){
        productionTime += job.first;
        result = max(result, productionTime + (ll)job.second);
    }

    cout << result << "\n";
    return 0;
}