#include <bits/stdc++.h>

using namespace std;

const int N = 2e4+10; // at most 2x
int dp[N];

void solve() {
    int M, n;
    cin >> M >> n;
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        for (int i = 0; i+x < N; i++) {
            dp[i+x] = min(dp[i+x], dp[i] + y);
        }
    }
    int res = dp[M];
    for (int i = M; i < N; i++) {
        res = min(res, dp[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
