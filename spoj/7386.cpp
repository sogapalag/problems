#include <bits/stdc++.h>

using namespace std;


void solve() {
    const int mod = 1e8;
    while (1) {
        int n; cin >> n;
        if (n == -1) {
            break;
        }
        vector<pair<int, int>> a(n+1);
        a[0] = {0, 0};
        for (int i = 1; i <= n; i++) {
            cin >> a[i].second >> a[i].first;
        }
        sort(a.begin(), a.end());
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i] += dp[i-1];
            auto it = upper_bound(a.begin(), a.end(), make_pair(a[i].second, a[i].second));
            int k = it - a.begin();
            dp[i] += dp[k-1];
            dp[i] %= mod;
        }
        int res = (dp[n] - 1 + mod) % mod;
        cout << setfill('0') << setw(8) << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
