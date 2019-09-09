#include <bits/stdc++.h>

using namespace std;

int a[3][111];
int dp[3][111];
void solve() {
    int m; cin >> m;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = a[i][j] + max(dp[i-1][j], dp[i][j-1]);
        }
    }
    cout << dp[2][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
