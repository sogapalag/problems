#include <bits/stdc++.h>

using namespace std;

int a[22][22];
long long dp[1<<20];
void solve() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        // TLE
       // for (int i = 0; i < n; i++) {
       //     for (int j = 0; j < n; j++) {
       //         for (int msk = 0; msk < 1<<n; msk++) {
       //             if (__builtin_popcount(msk) == i && a[i][j] && !(msk & (1<<j))) {
       //                 dp[msk ^ (1<<j)] += dp[msk];
       //             }
       //         }
       //     }
       // }
        // why below update work?
        // think this way, msk stictly less than msk|(1<<j)
        // so a state updated only by less state msk, which also updated.
        for (int msk = 0; msk < 1<<n; msk++) {
            int i = __builtin_popcount(msk);
            for (int j = 0; j < n; j++) {
                if (a[i][j] && !(msk & (1<<j))) {
                    dp[msk | (1<<j)] += dp[msk];
                }
            }
        }
        cout << dp[(1<<n)-1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
