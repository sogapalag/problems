#include <bits/stdc++.h>

using namespace std;

const int L = 18; 
int a[2][L];
int dp[L][1<<L]; // i-card as last of msk, #inversion

// the key is note that i-card be k-pos, a[0/1] parity related to (i,k)
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[0][i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[1][i];
    }
    const int INF = 0x3f3f3f3f;
    memset(dp, 0x3f, sizeof dp);
    const int MSK = 1<<n; 
    for (int i = 0; i < n; i++) {
        dp[i][1<<i] = 0;
    }
    for (int msk = 1; msk < MSK; msk++) {
        int cbit = 0;
        int p = __builtin_popcount(msk)&1;
        for (int i = n-1; i >= 0; i--) {
            if (msk>>i&1) cbit++;
            else {
                int x = a[p^(i&1)][i];
                for (int j = 0; j < n; j++) {
                    if (msk>>j&1) {
                        if (dp[j][msk] >= INF) continue;
                        int y = a[p^(j&1)^1][j];
                        if (y <= x) {
                            dp[i][msk|1<<i] = min(dp[i][msk|1<<i], dp[j][msk] + cbit);
                        }
                    }
                }
            }
        }
    }
    int res = INF;
    for (int i = 0; i < n; i++) {
        res = min(res, dp[i][MSK-1]);
    }
    if (res >= INF) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
