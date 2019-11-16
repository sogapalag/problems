#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const long long INF = 0x3f3f3f3f3f3f3f3f;
const int N = 303; 
ll dp[N][N]; // i) is last undelete, j=#undelete

// modify a[i] equiv, delete a[i]
void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    if (n == K) {
        cout << 0; return;
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        dp[i+1][1] = a[i];
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k < i; k++) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[k+1][j] + max(0, a[i] - a[k]));
            }
        }
    }
    ll res = INF;
    for (int i = 0; i <= n; i++) {
        res = min(res, dp[i][n-K]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
