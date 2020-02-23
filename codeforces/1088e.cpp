#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

    vector<ll> dp(n); // max sum for future connect
    // find max nonempty sum
    function<ll(int,int)> find = [&](int u, int p){
        ll mx = -1e18;
        dp[u] = a[u];
        for (int v:g[u])if(v!=p){
            mx = max(mx, find(v,u));
            dp[u] += dp[v];
        }
        mx = max(mx, dp[u]); if(dp[u]<0) dp[u] = 0;
        return mx;
    };
    ll mx = find(0,-1);
    
    int cnt = 0;
    // count how many mx, greedy cut out if find.
    function<void(int,int)> dfs = [&](int u, int p){
        dp[u] = a[u];
        for (int v:g[u])if(v!=p){
            dfs(v,u);
            dp[u] += dp[v];
        }
        if (dp[u] == mx) {
            cnt++; dp[u] = 0;
        } else if (dp[u] < 0) {
            dp[u] = 0;
        }
    };
    dfs(0, -1);

    cout << mx*cnt << ' ' << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
