#include <bits/stdc++.h>

using namespace std;

const int N = 122; 
int dp[N][2][4];

// at most 100^3 * 10^3
// one can also dfs, while optim 10^3 part, *x. but need detail-impl. omit
void solve() {
    string s; cin >> s;
    int n = s.size();
    int K; cin >> K;
    dp[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
        int x = s[i]-'0';
        for (int j:{0,1}) {
            for (int d = 0; d <= 9; d++) if(j || d<=x){
                for (int k: {0,1,2,3}) {
                    int nj = j || d<x;
                    int nk = k + (d>0);
                    if (nk <= 3) {
                        dp[i+1][nj][nk] += dp[i][j][k];
                    }
                }
            }
        }
    }
    int res = dp[n][0][K] + dp[n][1][K];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
