#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int m; cin >> m;
    vector<array<int,2>> pref(n + 1); // max-extend left end crt with 'a'/'b'
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a' || s[i] == '?') {
            pref[i+1][0] = pref[i][1] + 1;
        }
        if (s[i] == 'b' || s[i] == '?') {
            pref[i+1][1] = pref[i][0] + 1;
        }
        sum[i+1] = sum[i] + (s[i]=='?');
    }
    
    vector<array<int,2>> dp(n + 1); // 0 cnt, 1 cost
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        // greedy match while we can
        if (pref[i][(m&1)^1] >= m) {
            if (dp[i-m][0] + 1 > dp[i][0]) {
                dp[i] = {dp[i-m][0] + 1, dp[i-m][1] + (sum[i] - sum[i-m])};
            } else if (dp[i-m][0] + 1 == dp[i][0]) {
                dp[i][1] = min(dp[i][1], dp[i-m][1] + (sum[i] - sum[i-m]));
            }
        }
    }
    cout << dp[n][1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
