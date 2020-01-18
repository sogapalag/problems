#include <bits/stdc++.h>

using namespace std;


// the key is note from some u, d cannot keep dec. and must some dx=dy, let it be root.
//   otherwise d_nei(v)>dv, implies -1.
// then just dfs(try flip-color) forest, simply let cost_i = dv
//   this is true, as long as it hold above property, it must be visited
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<vector<pair<int,int>>> g(n);
    vector<bool> root(n);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        if (a[x] <= a[y]) g[x].emplace_back(y,i);
        if (a[y] <= a[x]) g[y].emplace_back(x,i);
        if (a[x] == a[y]) root[x] = true;
    }
    vector<int> co(n, -1);
    vector<int> cost(m, 1e9);
    function<bool(int,int)> dfs = [&](int u, int c){
        if (co[u] != -1) return false;
        co[u] = c;
        for (auto& e: g[u]) {
            int v,i;
            tie(v,i) = e;
            if (dfs(v, c^1)) {
                cost[i] = a[v];
            }
        }
        return true;
    };
    for (int i = 0; i < n; i++) {
        if (root[i] && co[i]==-1) dfs(i, 0);
    }
    for (int i = 0; i < n; i++) {
        if (co[i]==-1) {
            cout << -1; return;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (co[i]?'B':'W');
    }cout << '\n';
    for (int x:cost) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
