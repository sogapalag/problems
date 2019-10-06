#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 5555; 
const int Z = 2555;
ll dp[55][N];

void solve() {
    int n, A;
    cin >> n >> A;
    dp[0][Z] = 1;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x -= A;
        memcpy(dp[i+1], dp[i], sizeof dp[i+1]);
        for (int j = 0; j < N; j++) {
            if (j+x < 0 || j+x >= N) continue;
            dp[i+1][j+x] += dp[i][j];
        }
    }
    ll res = dp[n][Z] - 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
