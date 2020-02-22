#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int N = 5012; 
ll dp[N][2][N]; // 1/0 used coupon or not
ll convo[2][N];
void solve() {
    int n, B;
    cin >> n >> B;
    vector<int> c(n), d(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> d[i];
        if (i > 0) {
            int z; cin >> z; z--;
            g[z].push_back(i);
        }
    }

    memset(dp, 0x3f, sizeof dp);
    vector<int> sz(n);
    for (int u = n-1; u >= 0; u--) {
        dp[u][0][0] = 0;
        for (int v:g[u]) {
            memset(convo[0], 0x3f, sizeof(ll)* (sz[u]+sz[v]+1));
            memset(convo[1], 0x3f, sizeof(ll)* (sz[u]+sz[v]+1));
            for (int i = 0; i <= sz[u]; i++) {
                for (int j = 0; j <= sz[v]; j++) {
                    convo[0][i+j] = min(convo[0][i+j], dp[u][0][i] + dp[v][0][j]);
                    convo[1][i+j] = min(convo[1][i+j], dp[u][0][i] + dp[v][1][j]);
                    convo[1][i+j] = min(convo[1][i+j], dp[u][1][i] + dp[v][0][j]);
                    convo[1][i+j] = min(convo[1][i+j], dp[u][1][i] + dp[v][1][j]);
                }
            }
            sz[u] += sz[v];
            memcpy(dp[u][0], convo[0], sizeof(ll)* (sz[u]+1));
            memcpy(dp[u][1], convo[1], sizeof(ll)* (sz[u]+1));
        }
        ++sz[u];
        for (int i = sz[u]; i >= 1; i--) {
            // buy u or not, if buy must not use coupon
            dp[u][0][i] = min(dp[u][0][i], dp[u][0][i-1] + c[u]);
            // since u must used coupon, sub 0or1
            dp[u][1][i] = min(dp[u][0][i-1], dp[u][1][i-1]) + (c[u]-d[u]);
        }
    }

    for (int i = 0; i <= n; i++) {
        if (min(dp[0][0][i + 1], dp[0][1][i + 1]) > B) {
            cout << i; return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
