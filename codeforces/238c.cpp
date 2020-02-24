#include <bits/stdc++.h>

using namespace std;


// if A root, then all direct down.
//  if has B, then exist a vertical path up.
//  so dp[u] = max (#up - #down), find the max diff.
void solve() {
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].emplace_back(y, 0);
        g[y].emplace_back(x, 1);
    }

    int tot = 0;
    vector<int> dp(n);
    function<void(int,int)> dfs = [&](int u, int p){
        int mx = 0;
        for (auto [v,x]:g[u])if(v!=p){
            tot += x;
            dfs(v,u);
            int tmp = x - !x;
            tmp += dp[v];
            mx = max(mx, tmp);
        }
        dp[u] = mx;
    };
    int res = n;
    for (int i = 0; i < n; i++) {
        tot = 0; dfs(i,-1);
        tot -= *max_element(dp.begin(), dp.end());
        res = min(res, tot);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
