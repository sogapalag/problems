#include <bits/stdc++.h>

using namespace std;

int dp[44][444][444];

void solve() {
    int n, A,B;
    cin >> n >> A >> B;

    memset(dp, 0x3f, sizeof dp);
    dp[0][0][0] = 0;
    int res = 0x3f3f3f3f;
    for (int i = 0; i < n; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        for (int j = 0; j < 401; j++) {
            for (int k = 0; k < 401; k++) {
                dp[i+1][j][k] = dp[i][j][k];
            }
        }
        for (int j = 0; j < 401; j++) {
            for (int k = 0; k < 401; k++) {
                int& nxt = dp[i+1][j+x][k+y];
                nxt = min(nxt, dp[i][j][k]+z);
            }
        }
    }
    for (int j = 1; j < 401; j++) {
        for (int k = 1; k < 401; k++) {
            if (j*B == k*A) res = min(res, dp[n][j][k]);
        }
    }
    if (res == 0x3f3f3f3f) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
