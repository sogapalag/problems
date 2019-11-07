#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<int> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
            r[i] = 1;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x; r[x] += r[y];
        return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

// bfs on 0-graph
// remain compo must use 1-edge to connect
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> deg(n, 0);
    vector<set<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        g[x].insert(y);
        g[y].insert(x);
        deg[x]++; deg[y]++;
    }
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](auto& u, auto& v){
        return deg[u] < deg[v];
    });
    // by sort deg, sum wit ~O(n+m). need rigorous.
    set<int> wit;
    for (int i = 0; i < n; i++) {
        wit.insert(i);
    }
    Dsu d(n);
    vector<bool> trk(n);
    for (int u: id) {
        if (wit.empty()) break;
        if (trk[u]) continue;
        if (wit.find(u) != wit.end()) wit.erase(u);
        queue<int> q;
        q.push(u);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            trk[u] = true;
            set<int> con;
            for (int v: wit) {
                if (g[u].find(v) == g[u].end()) {
                    con.insert(v);
                    q.push(v);
                    d.join(u, v);
                }
            }
            for (int v: con) {
                wit.erase(v);
            }
        }
    }
    set<int> pa;
    for (int i = 0; i < n; i++) {
        pa.insert(d.find(i));
    }
    int res = pa.size() - 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
