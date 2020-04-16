#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int _ = 1; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> sz(n, 1);
    vector<int> depth(n, 1);
    function<void(int,int)> dfs = [&](int u, int p){
        for (int v: g[u])if(v!=p){
            depth[v] += depth[u];
            dfs(v, u);
            sz[u] += sz[v];
        }
    };
    dfs(0,-1);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = depth[i] - sz[i]; // each contribution
    }
    sort(a.begin(), a.end());
    long long res = 0;
    for (int i = 1; i <= k; i++) {
        res += a[n-i];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
