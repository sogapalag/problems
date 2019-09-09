#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_diameter
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
    vector<int> pa;
    vector<int> d;
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (trk[v]) continue;
            pa[v] = u; d[v] = 1 + d[u];
            dfs(v);
        }
    }
    // for undirected tree
    vector<int> get_diameter() {
        pa.assign(n, -1);
        d.assign(n, 0);
        trk.assign(n, false);
        d[0] = 1; pa[0] = -1; dfs(0);
        int root = max_element(d.begin(), d.end()) - d.begin();
        fill(pos.begin(), pos.end(), 0);
        fill(trk.begin(), trk.end(), false);
        d[root] = 1; pa[root] = -1; dfs(root);
        int tail = max_element(d.begin(), d.end()) - d.begin();
        int num = d[tail];
        vector<int> pth(num);
        for (int i = num-1, x=tail; i >= 0; i--) {
            assert(x != -1);
            pth[i] = x;
            x = pa[x];
        }
        assert(pth[0] == root);
        return pth;
    }
};
// SNIPPETS_END
