#include <bits/stdc++.h>

using namespace std;

const int N = 404; 
int dp[N][N]; // use s[..i] , fullfill t[..j], 's max second length

void solve() {
    string s,t;
    cin >> s >> t;
    int n = s.size();
    int m = t.size();
    for (int a = 1; a <= m; a++) {
        memset(dp, -1, sizeof dp);
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= a; j++)if(dp[i][j]!=-1) {
                int k = a + dp[i][j];
                dp[i+1][j] = max(dp[i+1][j], dp[i][j] + (k<m && s[i]==t[k]));
                if(j<a && s[i]==t[j]) dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
            }
        }
        if (dp[n][a] >= m-a) {
            cout << "YES\n"; return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
