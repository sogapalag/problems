#include <bits/stdc++.h>

using namespace std;


void solve() {
    while (1) {
        string s; cin >> s;
        if (s[0] == '0') {
            break;
        }
        int n = s.size();
        vector<int> dp(n+1, 0);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (s[i-1] > '0')
                dp[i] += dp[i-1];
            string sub = s.substr(i-2, 2);
            if ("09" < sub && sub < "27")
                dp[i] += dp[i-2];
        }
        cout << dp[n] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
