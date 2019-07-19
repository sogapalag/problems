#include <bits/stdc++.h>

using namespace std;

using ll=long long ;


void solve() {
    int n; cin >> n;
    vector<int> a[2];
    for (int i = 0; i < 2; i++) {
        a[i].resize(n);
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<array<ll,3>> dp(n+1);
    dp[0] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        dp[i+1][0] = a[0][i] + max(dp[i][1], dp[i][2]);
        dp[i+1][1] = a[1][i] + max(dp[i][0], dp[i][2]);
        dp[i+1][2] = max({dp[i][1], dp[i][0], dp[i][2]});
    }
    ll res = max({dp[n][0], dp[n][1], dp[n][2]});
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
