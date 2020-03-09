#include <bits/stdc++.h>

using namespace std;

using pci = pair<char,int>;
void solve() {
    int n; cin >> n;
    vector<vector<pci>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        int x; char c;
        cin >> x >> c;
        g[x].emplace_back(c, i);
    }
    for (int i = 0; i < n; i++) {
        sort(g[i].begin(), g[i].end());
    }
    int m; cin >> m;
    vector<bool> is(n + 1);
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
        is[x] = true;
    }

    vector<int> dp(n + 1), sz(n + 1);
    // best, min use for autocomplement time.
    function<void(int,int)> dfs = [&](int u, int best){
        if (is[u]) {
            dp[u] = min(dp[u], best + 1); // autoc. 1-th
        }
        sz[u] = is[u];
        for (auto& _:g[u]) {
            int v = _.second;
            dp[v] = dp[u] + 1; // just type
            dfs(v, min(dp[u], best) + sz[u]); // prev u or best, now has redundent sz[u] autocomple.
            sz[u] += sz[v];
        }
    };
    dfs(0, n);

    for (int x:a)cout << dp[x] << ' ';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
