#include <bits/stdc++.h>

using namespace std;

int dp[52*35];
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++) {
        vector<int> a(m);
        for (auto& x: a) cin >> x;
        vector<int> sum(m+1);
        for (int i = 0; i < m; i++) {
            sum[i+1] = sum[i] + a[i];
        }
        for (int x = i*m; x >= 0; x--) {
            for (int j = m; j >= 1; j--) {
                dp[x+j] = max(dp[x+j], dp[x] + sum[j]);
            }
        }
    }
    cout << dp[k] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
