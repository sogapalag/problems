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
    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n+1);
    }
    Graph(int _n, int _m) : n(_n), m(_m) {
        assert(n >= 1);
        assert(1ll*n*(n-1)/2 >= m);
        g.resize(n+1);
        input();
    }
    inline void add(int u, int v) {
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u); // digraph remove
    }
    void input() {
        int u, v;
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            add(u, v);
        }
    }
};
// SNIPPETS_END
