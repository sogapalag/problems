#include <bits/stdc++.h>

using namespace std;

int dp[111][111];

// key: for a path, 001..110011. it's optimal and can do with #1-runs
void solve() {
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = s[0][0]=='#';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int _:{0,1}) {
                int x = i+_;
                int y = j+(_^1);
                if (x<n&&y<m) {
                    int more = (s[i][j]=='.' && s[x][y]=='#');
                    dp[x][y] = min(dp[x][y], dp[i][j] + more);
                }
            }
        }
    }
    cout << dp[n-1][m-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
