#include <bits/stdc++.h>

using namespace std;

// binary lifting, (or sparse table) store 1,2,4,8..th ancestors

// SNIPPETS_START graph_lca_bl
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

    static const int LOG = 18; // 21;
    int k;
    vector<int> up[LOG];
    int tim;
    vector<int> bg;
    vector<int> nd;
    void prep(int root);
    void _dfs(int u, int pa) {
        bg[u] = tim++;
        up[0][u] = pa;
        for (int j = 1; j <= k; j++) {
            up[j][u] = up[j-1][up[j-1][u]];
        }
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (v != pa) _dfs(v, u);
        }
        nd[u] = tim++;
    }
    inline bool _is_ancestor(int u, int v) {
        return bg[u] <= bg[v] && nd[u] >= nd[v];
    }
    inline int lca(int u, int v);
};
void Graph::prep(int root=0) {
    k = 32 - __builtin_clz(n);
    for (int j = 0; j <= k; j++) {
        up[j].resize(n);
    }
    bg = vector<int>(n, 0);
    nd = vector<int>(n, 0);
    tim = 1;
    _dfs(root, root);
}
inline int Graph::lca(int u, int v) {
    if (_is_ancestor(u, v)) return u;
    if (_is_ancestor(v, u)) return v;
    for (int j = k; j >= 0; j--) {
        if(!_is_ancestor(up[j][u], v))
            u = up[j][u];
    }
    return up[0][u];
}
// SNIPPETS_END
