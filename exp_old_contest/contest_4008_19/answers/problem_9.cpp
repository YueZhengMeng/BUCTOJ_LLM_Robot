/* 
  Vision Transformer Patch Summation
  - Partition each 3-channel image into 4x4 patches
  - Sum each patch per channel
  - Output flattened tokens (R_sum, G_sum, B_sum)
  - Append special token 'l','x','r' => (108,120,114)
*/
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    // Read 3 channels
    vector<vector<long long>> channel(3, vector<long long>(n * m));
    for(int c = 0; c < 3; c++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> channel[c][i * m + j];
            }
        }
    }

    int bn = n / 4, bm = m / 4;
    int tokens = bn * bm;
    // sums[c][k] = sum of channel c in block k
    vector<vector<long long>> sums(3, vector<long long>(tokens, 0LL));

    // Compute patch sums
    for(int c = 0; c < 3; c++){
        int idx = 0;
        for(int bi = 0; bi < bn; bi++){
            for(int bj = 0; bj < bm; bj++){
                long long s = 0;
                int baseRow = bi * 4;
                int baseCol = bj * 4;
                // sum over 4x4 block
                for(int di = 0; di < 4; di++){
                    for(int dj = 0; dj < 4; dj++){
                        s += channel[c][ (baseRow+di) * m + (baseCol+dj) ];
                    }
                }
                sums[c][idx++] = s;
            }
        }
    }

    // Output tokens in token-major order
    for(int k = 0; k < tokens; k++){
        cout << sums[0][k] << ' ' 
             << sums[1][k] << ' ' 
             << sums[2][k] << '\n';
    }
    // Append cls token 'l','x','r'
    cout << 108 << ' ' << 120 << ' ' << 114 << '\n';

    return 0;
}