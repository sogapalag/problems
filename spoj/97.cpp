#include <bits/stdc++.h>

using namespace std;

const int W = 512; 
const int N = 128; 
int cst[N], fun[N];
int dp[W][N];

void solve() {
    while (true) {
        int w, n;
        cin >> w >> n;
        if (!w && !n) return;
        for (int i = 1; i <= n; i++) {
            cin >> cst[i] >> fun[i];
        }
        memset(dp, 0, sizeof dp);
        for (int i = 1; i <= w; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i][j-1];
                if (cst[j] <= i) {
                    dp[i][j] = max(dp[i][j], dp[i-cst[j]][j-1] + fun[j]);
                }
            }
        }
        int res = dp[w][n];
        int ans = w;
        while (ans>0 && dp[ans][n] == res) {
            ans--;
        }
        ans++;
        cout << ans << " " << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
