#include <bits/stdc++.h>

using namespace std;
using ll=long long;
ll dp[512][512];

// a simple math. optimal is each triangle connect to 1. res = sum_{2..} i*(i+1)
void solve() {
    memset(dp, 0x3f, sizeof dp);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        dp[i][i+1] = 0;
        dp[i][i+2] = i*(i+1)*(i+2);
    }
    for (int d = 3; d <= n; d++) {
        for (int i = 1; i+d <= n; i++) {
            for (int j = i+1; j < i+d; j++) {
                ll tmp = (ll)i*(i+d)*j + dp[i][j] + dp[j][i+d];
                dp[i][i+d] = min(dp[i][i+d], tmp);
            }
        }
    }
    cout << dp[1][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
