#include <bits/stdc++.h>

using namespace std;


// same cf/190f, LIS on tree
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> dp(n+1, 2e9), len(n);
    dp[0] = 0;
    function<void(int,int)> dfs = [&](int u, int p){
        int k = lower_bound(dp.begin(), dp.end(), a[u]) - dp.begin();
        len[u] = max(len[u], k);
        int old = dp[k];
        dp[k] = a[u];
        for (int v: g[u])if(v!=p){
            // 1..v max 1..u
            len[v] = max(len[v], len[u]);
            dfs(v, u);
        }
        dp[k] = old;
    };
    dfs(0,-1);
    for (auto& x: len) {
        cout << x << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
