#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n + 1);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> sz(n + 1); // #subleaves
    vector<int> dp(n + 1); // 0-based, can be kth of subleaves of u
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        sz[u] = 0;
        int son = 0;
        int res = (depth&1) ? 0 : -1e7;
        for (int v: g[u])if(v!=p){
            son++;
            dfs(v, u, depth+1);
            if (depth&1) {
                // have to waste dp[v] each, then next would be min-player chosen
                res += dp[v];
            } else {
                // max-player choose it, greedy (sz[v])-largest to this sub. i.e. shift sz[u]-sz[v]
                // so wanna max dp[v] + sz[u]-sz[v]
                res = max(res, dp[v] - sz[v]);
            }
            sz[u] += sz[v];
        }
        if (!son) {
            sz[u]++;
            dp[u] = 0;
        } else if (depth&1){
            dp[u] = res;
        } else {
            dp[u] = res + sz[u];
        }
    };

    dfs(1, -1, 0);
    cout << dp[1] + 1 << ' ';

    g[0].push_back(1);
    dfs(0, -1, 0); // or dp(1, -1, 1)
    cout << sz[0] - dp[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
