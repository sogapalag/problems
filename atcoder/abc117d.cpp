#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    int n; ll k;
    cin >> n >> k;
    vector<int> cnt(70, 0);
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        for (int i = 0; i < 63; i++) {
            if (x & (1ll<<i))
                cnt[i]++;
        }
    }

    ll dp[66][2]; // 0 for prefix equal, 1 for neq
    memset(dp, -1, sizeof dp);
    dp[63][0] = 0;
    for (int i = 62; i >= 0; i--) {
        int x = cnt[i]; ll j = 1ll<<i;
        if (k & j) {
            dp[i][0] = max(dp[i][0], dp[i+1][0] + (n-x)*j);
            dp[i][1] = max(dp[i][1], dp[i+1][0] + x*j);
            if (dp[i+1][1] != -1) // -1 for -inf check, blocked, -1ll<<62 cannot ensure, since grow fast
            dp[i][1] = max(dp[i][1], dp[i+1][1] + max(x,n-x) * j);
        } else {
            dp[i][0] = max(dp[i][0], dp[i+1][0] + x*j);
            if (dp[i+1][1] != -1)
            dp[i][1] = max(dp[i][1], dp[i+1][1] + max(x,n-x) * j);
        }
    }
    ll res = max(dp[0][0], dp[0][1]);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
