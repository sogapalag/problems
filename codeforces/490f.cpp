#include <bits/stdc++.h>

using namespace std;


// LIS on tree, O(n^2 log n). TODO O(n)/O(n log n)
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

    int res = 0;
    vector<int> dp(n + 1);
    function<void(int,int)> dfs = [&](int u, int p){
        // knuth
        int k = lower_bound(dp.begin(), dp.end(), a[u]) - dp.begin();
        res = max(res, k);
        int old = dp[k]; // need restore, since switch substree
        dp[k] = a[u];
        for (int v: g[u])if(v!=p){
            dfs(v, u);
        }
        dp[k] = old;
    };
    // iter i as root lower-end
    for (int i = 0; i < n; i++) {
        fill(dp.begin(), dp.end(), 1<<28);
        dp[0] = 0;
        dfs(i, -1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
