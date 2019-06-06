#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_bellman_ford
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
        int u, v, c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c;
            u--; v--; // input 1-based
            add(u, v, c);
        }
    }
    template <typename T=int>
    vector<T> bellman_ford(int s);
};

// single source shortest path
// allow negative, but not -cycle
template <typename T>
vector<T> Graph::bellman_ford(int s) {
    const int INF = 0x3f3f3f3f;
    vector<T> d(n, INF);
    d[s] = 0;
    // if detect, add another round
    for (int i = 0; i < n-1; i++) {
        // add flag early stop for constant optimization
        for (auto& k: e) {
            if (d[k.u] < INF && d[k.v] > d[k.u] + k.cost)
                d[k.v] = d[k.u] + k.cost;
        }
    }
    return d;
}
// SNIPPETS_END
