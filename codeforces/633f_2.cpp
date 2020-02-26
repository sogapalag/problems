#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// much elegant. note there're 4 state,
// shape as
// |;  n;  n|;  n n
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    auto maxi = [&](ll& x, ll y){
        if (x < y) x = y;
    };
    vector<array<ll,4>> dp(n);
    vector<ll> dn(n); // under u. replace with [u][1], i.e. n shape, since when merge, n-shape cannot pass u.
    function<void(int,int)> dfs = [&](int u, int p){
        fill(dp[u].begin(), dp[u].end(), a[u]);
        for (int v:g[u])if(v!=p){
            dfs(v,u);
            maxi(dp[u][3], dp[v][3]);
            for (int i:{0,1,2}){
                maxi(dp[u][3], dp[u][i] + dp[v][2-i]);
            }

            maxi(dp[u][2], dp[v][2] + a[u]);
            maxi(dp[u][2], dp[u][0] + dp[v][1]);
            maxi(dp[u][2], dn[u] + dp[v][0] + a[u]);

            maxi(dn[u], dp[v][1]);
            maxi(dp[u][1], dp[v][1]);
            maxi(dp[u][1], dp[u][0] + dp[v][0]);

            maxi(dp[u][0], dp[v][0] + a[u]);
        }
    };
    dfs(0,-1);
    cout << dp[0][3];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
