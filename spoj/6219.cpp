#include <bits/stdc++.h>

using namespace std;


void solve() {
    string a, b;
    cin >> a;
    cin >> b;
    int n = a.size();
    int m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i-1][j-1] + (a[i-1] == b[j-1]? 0 : 1);
            dp[i][j] = min({dp[i][j], dp[i-1][j]+1, dp[i][j-1]+1});
        }
    }
    cout << dp[n][m] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    cout << endl;
}
