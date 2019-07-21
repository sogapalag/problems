#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
    for (int j = 1; j <= m; j++) {
        dp[1][j] = s[0][j-1] == 'O';
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i-1][j-1] != 'O') continue;
            dp[i][j] = dp[i-1][j-1] | dp[i][j-1];
        }
    }
    int res = -1;
    for (int j = 1; j <= m; j++) {
        if (dp[n][j]) {
            res = j; break;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
