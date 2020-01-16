#include <bits/stdc++.h>

using namespace std;

const int N = 512; 
int dp[N][N];

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    memset(dp, 0x3f, sizeof dp);
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        dp[i][i+1] = 1;
    }
    for (int d = 2; d <= n; d++) {
        for (int i = 0; i+d <= n; i++) {
            int& x = dp[i][i+d];
            x = min(x, 1 + dp[i+1][i+d]);
            for (int j = i+1; j < i+d; j++) {
                if (s[i] == s[j])
                    x = min(x, dp[i+1][j] + dp[j][i+d]);
            }
        }
    }
    cout << dp[0][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
