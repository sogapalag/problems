#include <bits/stdc++.h>

using namespace std;

int comp(int x, int y) {
    return x < y ? -1 : (x == y ? 0 : 1);
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<array<int,4>> dp(n, {n,n,n,n});
    for (int x = 0; x < 4; x++) {
        dp[0][x] = 0;
    }
    for (int i = 1; i < n; i++) {
        int c = comp(a[i-1], a[i]);
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                dp[i][y] = min(dp[i][y], dp[i-1][x] + (comp(x,y)!=c));
            }
        }
    }
    int res = n;
    for (int x = 0; x < 4; x++) {
        res = min(res, dp[n-1][x]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
