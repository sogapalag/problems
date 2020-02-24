#include <bits/stdc++.h>

using namespace std;
using ll=long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int K = 12; 
const int N = 88; 
int g[N][N];
int co[N];
ll dp[K][N];

// FPT
// random assign color, 2^{k-1} prob,
void solve() {
    clock_t begin = clock();
    int n,k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    ll res = 1e18;
    while (clock() - begin <= 2800) {
        for (int i = 0; i < n; i++) {
            co[i] = rng()&1;
        }
        memset(dp, 0x3f, sizeof dp);
        dp[0][0] = 0;
        for (int t = 0; t < k; t++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (co[i]!=co[j]) {
                        dp[t+1][i] = min(dp[t+1][i], dp[t][j] + g[j][i]);
                    }
                }
            }
        }
        res = min(res, dp[k][0]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
