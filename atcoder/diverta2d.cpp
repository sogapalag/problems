#include <bits/stdc++.h>

using namespace std;

using ll=long long;

void solve() {
    int n; cin >> n;
    int a[3], b[3];
    cin >> a[0] >> a[1] >> a[2];
    cin >> b[0] >> b[1] >> b[2];
    vector<ll> dp(n+1, 0);
    vector<int> v(3);
    for (int i = 0; i < 3; i++) {
        v[i] = b[i] - a[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[j] <= i) {
                dp[i] = max(dp[i], dp[i-a[j]] + v[j]);
            }
        }
    }
    int m = n + dp[n];
    dp.assign(m+1, 0);
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[j] <= i) {
                dp[i] = max(dp[i], dp[i-b[j]] - v[j]);
            }
        }
    }
    ll res = m + dp[m];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
