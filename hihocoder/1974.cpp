#include <bits/stdc++.h>

using namespace std;

int dp[50][1<<20];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> d(m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            int k = (x >= a[j]);
            d[i] |= k << j;
        }
    }

    int tot = 0;
    for (int i = 0; i < m; i++) {
        tot |= d[i];
    }
    if (tot != (1<<n)-1) {
        cout << -1; return;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    if (d[0])
        dp[0][d[0]] = 1;
    for (int i = 1; i < m; i++) {
        for (int msk = 0; msk < (1<<n); msk++) {
            dp[i][msk] = min(dp[i][msk], dp[i-1][msk]);
            dp[i][msk| d[i]] = min(dp[i][msk|d[i]], dp[i-1][msk] + 1);
        }
    }
    cout << dp[m-1][(1<<n)-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
