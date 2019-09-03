#include <bits/stdc++.h>

using namespace std;

// graph, digraph, forest, simple, connected.
// with differen kinds of edge.
// a general implement might useful, but painful to impl.
// here impl (simple) graph, for most use case.

// SNIPPETS_START graph_sim
struct Graph {
    int n, m;
    vector<vector<int>> g;
    bool is_digraph;
    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), m(0) {
        assert(n >= 1);
        assert(1ll*n*(n-1)/2 >= m);
        g.resize(n);
        set_di(_di);
        input(_m);
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        if (!is_digraph)
            g[v].emplace_back(u);
        m++;
    }
    void input(int _m) {
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--;v--; // to 0-based
            add(u, v);
        }
    }
    void set_di(bool _di) {
        is_digraph = _di;
        trk = vector<bool>(n, false);
    }
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (int v: g[u]) {
            if (trk[v]) continue;
            //
        }
    }
};
// SNIPPETS_END
