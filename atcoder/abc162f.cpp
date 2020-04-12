#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 2e5+10; 
int a[N];
ll dp[3][N];
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int hole = 1 + (n&1);
    memset(dp, 0xc0, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= hole; j++) {
            for (int k = 0; k+j <= hole; k++) {
                int ii = i + (i>0) + k;
                dp[k+j][ii+1] = max(dp[k+j][ii+1], dp[j][i] + a[ii]);
            }
        }
    }
    ll res = max(dp[hole][n], dp[hole-1][n-1]);
    if (hole == 2) res = max(res, dp[hole-2][n-2]);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
