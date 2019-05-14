#include <bits/stdc++.h>

using namespace std;


void solve() {
    const int N = 111; 
    int dp[N][N];
    int T; cin >> T;
    while (T--) {
        int h, w;
        cin >> h >> w;
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                cin >> dp[i][j];
            }
        }
        for (int i = h-1; i >= 1; i--) {
            for (int j = 1; j <= w; j++) {
                dp[i][j] += max({dp[i+1][j-1], dp[i+1][j], dp[i+1][j+1]});
            }
        }
        int res = 0;
        for (int j = 1; j <= w; j++) {
            res = max(res, dp[1][j]);
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
