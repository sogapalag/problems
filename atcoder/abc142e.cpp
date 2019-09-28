#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int L = 12;

int dp[1<<L];

void solve() {
    int n,m;
    cin >> n >> m;
    const int MSK = 1<<n;

    memset(dp, INF, sizeof dp);
    dp[0] = 0;
    for (int _ = 0; _ < m; _++) {
        int cost, _n;
        cin >> cost >> _n;
        int k = 0;
        for (int __ = 0; __ < _n; __++) {
            int x; cin >> x;
            k |= 1<<(x-1);
        }

        for (int msk = MSK-1; msk >= 0; msk--) {
            dp[msk|k] = min(dp[msk|k], dp[msk] + cost);
        }
    }
    if (dp[MSK-1] == INF) dp[MSK-1] = -1;
    cout << dp[MSK-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
