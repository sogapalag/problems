#include <bits/stdc++.h>

using namespace std;

const int N = 6111; 
int dp[N][N];

void solve() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        memset(dp, 0, sizeof dp);
        for (int d = 1; d < n; d++) {
            for (int i = 0; i < n-d; i++) {
                if (s[i] == s[i+d]) {
                    dp[d][i] = d == 1 ? 0 : dp[d-2][i+1];
                } else {
                    dp[d][i] = 1 + min(dp[d-1][i], dp[d-1][i+1]);
                }
            }
        }
        cout << dp[n-1][0] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
