#include <bits/stdc++.h>

using namespace std;


// expand each edge to 3 edge. Z3 group
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(3*n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y+n);
        g[x+n].emplace_back(y+2*n);
        g[x+2*n].emplace_back(y);
    }
    int s, t; cin >> s >> t;
    s--; t--;
    vector<int> d(3*n, 0);
    auto bfs = [&](){
        queue<int> q;
        d[s] = 0;
        q.emplace(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: g[u]) {
                if (!d[v]) {
                    d[v] = d[u] + 1;
                    q.emplace(v);
                }
            }
        }
    };
    bfs();
    int res = d[t]? d[t]/3: -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
