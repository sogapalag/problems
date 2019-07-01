#include <bits/stdc++.h>

using namespace std;
using ll=long long;
// note first choose decide the points.
// so first dfs get 0's point.
// then second dfs, note neib.'s diff, n-2*sz
// never use similar dfs function name again!!!
// dfs2 { dfs(); }... fk!
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    vector<int> sz(n, 0);
    vector<bool> trk(n, false);
    vector<ll> pt(n, 0);
    function<void(int)> dfs = [&](int u) {
        trk[u] = true;
        sz[u] = 1;
        for (int v: g[u]) {
            if (!trk[v]) {
                dfs(v);
                sz[u] += sz[v];
                pt[u] += pt[v];
            }
        }
        pt[u] += sz[u];
    };
    function<void(int)> down = [&](int u) {
        trk[u] = true;
        for (int v: g[u]) {
            if (!trk[v]) {
                pt[v] = pt[u] + n - 2*sz[v];
                down(v);
            }
        }
    };
    dfs(0);
    trk.assign(n, false);
    down(0);
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, pt[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
