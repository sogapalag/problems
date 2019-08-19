#include <bits/stdc++.h>

using namespace std;

int dp[200'005][2];

// |S_i|<=2
void solve() {
    string s; cin >> s;
    int n = s.size();
    memset(dp, -1, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i < n; i++) {
        dp[i][0] = dp[i-1][1]+1;
        if (s[i] != s[i-1])
            dp[i][0] = max(dp[i][0], dp[i-1][0]+1);

        dp[i][1] = i<3? (i<2?1:2): dp[i-2][0]+1;
        if (i>=3 && (s[i] != s[i-2] || s[i-1] != s[i-3]))
            dp[i][1] = max(dp[i][1], dp[i-2][1]+1);
    }
    int res = max(dp[n-1][0], dp[n-1][1]);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
