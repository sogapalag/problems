#include <bits/stdc++.h>

using namespace std;

struct Graph {
    struct Edge {
        int u, v;
        int cost;
        Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    bool is_digraph;
    vector<vector<int>> g;
    vector<Edge> e;

    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
    }
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            //deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--; v--; // input 1-based
            add(u, v);
        }
    }
    vector<int> pos;
    vector<bool> trk;
    vector<int> sz;
    vector<long long> res;
    void sz_dfs(int u) {
        trk[u] = true;
        sz[u] = 1;
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            if (!trk[v]) {
                sz_dfs(v);
                sz[u] += sz[v];
            }
        }
    }
    void opt_dfs(int u) {
        trk[u] = true;
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            if (!trk[v]) {
                res[v] = res[u] + 1ll* (sz[u] - sz[v]) * sz[v];
                opt_dfs(v);
            }
        }
    }
    long long run() {
        trk.assign(n, false); pos.assign(n, 0);
        sz.assign(n, 0);
        sz_dfs(0);
        trk.assign(n, false); pos.assign(n, 0);
        res.assign(n, 0);
        opt_dfs(0);
        long long mx=0; int u = -1;
        for (int i = 0; i < n; i++) {
            if (res[i] > mx) {
                mx = res[i];
                u = i;
            }
        }
        assert(~u);
        trk.assign(n, false); pos.assign(n, 0);
        sz.assign(n, 0);
        sz_dfs(u);
        trk.assign(n, false); pos.assign(n, 0);
        res.assign(n, 0);
        opt_dfs(u);
        mx = 0;
        for (int i = 0; i < n; i++) {
            if (res[i] > mx) {
                mx = res[i];
            }
        }
        return 1ll*n*(n-1)/2 + mx;
    }
};

// first note, optimal is a leaf to leaf path.
// kind like find diamter, every step down, increase those could pass
void solve() {
    int n; cin >> n;
    Graph g(n, n-1);
    cout << g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
