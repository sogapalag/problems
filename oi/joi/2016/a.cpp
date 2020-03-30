#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<ll> dp(n + 1, 1ll<<61);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int mx = 0, mi = 2e9;
        for (int j = i; j >= 0 && j > i-m; j--) {
            mx = max(mx, a[j]);
            mi = min(mi, a[j]);
            dp[i+1] = min(dp[i+1], dp[j] + k + (i-j+1) * 1ll * (mx-mi));
        }
    }
    cout << dp[n] << '\n'; // atcoder, summit, need '\n'
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
