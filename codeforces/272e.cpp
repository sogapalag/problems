#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        deg[x]++; deg[y]++;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // there won't be inf-cycle.
    // since each flip some bad u, at least -2 same-group edge(by deg>1), at most +1 same-group edge(by real-deg<=3).
    //   thus, each time at least -1 sg-edge
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] > 1) q.push(i);
    }
    vector<int> co(n, 0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (deg[u] <= 1) continue;
        for (int v: g[u]) {
            if (co[u] == co[v]) deg[u]--,deg[v]--;
            else deg[u]++,deg[v]++;
            if (deg[v] > 1) q.push(v);
        }
        co[u] ^= 1;
    }
    for (int x: co)cout << x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
