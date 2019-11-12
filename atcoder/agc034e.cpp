#include <bits/stdc++.h>

using namespace std;


// when fix root, if after subtree ops, only consider lca=root ops.
// let sd[v](subtree depth sum) x1,x2,...
// we wanna make all x ->0, by each time select two x both -1.
//   valid <=> oth = sum - max >= max, dp[u] = by parity 0 or 1
//    otherwise dp[u] = max-oth
//
// so maintain dp as min-sum-depth.
// check max dp[v] <= sum-sd[v]?
// 
// note below comment also valid, since for max (dp[v]+sd[v]), dp[v] <= dp[v*] <= sd[v*]<= sum[v]-sd[v].
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    vector<int> dp(n), sd(n), sz(n);
    function<void(int,int)> dfs = [&](int u, int p){
        sz[u] = s[u]-'0';
        sd[u] = 0;
        int mx = 0, mi = 0;
        for (int v: g[u])if(v!=p){
            dfs(v, u);
            sz[u] += sz[v];
            sd[u] += (sd[v] += sz[v]);
            dp[v] += sz[v];
            //if (mx < dp[v]) {
            //    mx = dp[v]; mi = sd[v];
            //} else if (mx == dp[v]) {
            //    mi = min(mi, sd[v]);
            //}
            mx = max(mx, dp[v] + sd[v]);
        }
        //if (mx <= sd[u] - mi) dp[u] = sd[u]&1;
        //else dp[u] = mx + mi - sd[u];
        if (mx <= sd[u]) dp[u] = sd[u]&1;
        else dp[u] = mx - sd[u];
    };
    
    int res = 1<<28;
    for (int i = 0; i < n; i++) {
        dfs(i,-1);
        if (dp[i] == 0) {
            res = min(res, sd[i]/2);
        }
    }
    if (res == 1<<28) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
