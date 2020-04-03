#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int L = 35; 
ll a[L];
ll dp[L][L];

// key, MSB inc, 1. 1.. 1.... 1.......
void solve() {
    int n,m;
    cin >> n >> m;
    memset(a, 0, sizeof a);
    memset(dp, 0, sizeof dp);
    int h = 31-__builtin_clz(n);
    for (int i = 0; i < h; i++) {
        a[i] = 1<<i;
    }
    a[h] = n - (1<<h) + 1;
    h++;
    ll res = 0;
    dp[0][0] = 1;
    for (int i = 0; i < h; i++) {
        for (int j = i; j < h; j++) {
            for (int k = j+1; k <= h; k++) {
                (dp[i+1][k] += dp[i][j] * a[k-1]) %= m;
            }
        }
    }
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= h; j++) {
            (res += dp[i][j]) %= m;
        }
    }
    cout << res << "\n";
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
