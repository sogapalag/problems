#include <bits/stdc++.h>

using namespace std;

// key: note the min-path must be 1-edges, i.e. a 2-edge never be in min-path
//      so, can treat it as delete(time-reversal)
// key optimization: bfs(or dfs) only when d[v] just :=D[v]. thus each v update at most once, whole time.
void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    vector<pair<int, int>> es(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        es[i] = {x,y};
        g[x].push_back(i);
        g[y].push_back(i);
    }
    vector<int> qrs(q);
    vector<bool> trk(m);
    for (auto& x: qrs) {
        cin >> x; x--;
        trk[x] = true;
    }
#define fi first
#define se second
    vector<int> D(n, 1e9);
    {
        D[0] = 0;
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i:g[u]) {
                int v = es[i].fi ^ es[i].se ^ u;
                if (D[v] > D[u] + 1) {
                    D[v] = D[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    vector<int> d(n, 1e9);
    {
        d[0] = 0;
        queue<int> q; q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i:g[u])if(!trk[i]) {
                int v = es[i].fi ^ es[i].se ^ u;
                if (d[v] > d[u] + 1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    auto explore = [&](int r){
        queue<int> q; q.push(r);
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cnt++;
            for (int i:g[u])if(!trk[i]){
                int v = es[i].fi ^ es[i].se ^ u;
                if (d[v] > D[v] && D[v] == d[u]+1) {
                    d[v] = D[v];
                    q.push(v);
                }
            }
        }
        return cnt;
    };
    vector<int> delta(q);
    for (int _ = q-1; _ >= 0; _--) {
        int i = qrs[_]; trk[i] = false;
        int u,v;
        tie(u,v) = es[i];
        if (d[u] > d[v]) swap(u, v);
        if (d[u] == D[u] && d[v] > D[v] && D[v] == d[u]+1) {
            d[v] = d[u]+1;
            delta[_] = explore(v);
        }
    }
    int res = 0;
    for (int x:delta) {
        res += x;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
