#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_centroid_decomp
// for tree use
struct Graph {
    using CT = int; static const CT INF = 0x3f3f3f3f;
    //using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int u, v;
        CT cost;
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
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
    inline void add(int u, int v, CT cost=1) {
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
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        pa = vector<int>(n, -1);
        sz = vector<int> (n, 1);
        trk = vector<bool> (n, false);
        is_digraph = _di;
    }
    
    vector<int> pos;
    vector<int> pa;
    vector<int> sz;
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            pa[v] = u;
            dfs(v);
            sz[u] += sz[v];
        }
    }
    vector<int> centroids(){
        dfs(0);
        vector<int> cds;
        for (int u = 0; u < n; u++) {
            bool yes = true;
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (v!=pa[u]) yes &= sz[v] <= n/2;
            }
            yes &= n-sz[u] <= n/2;
            if (yes) cds.emplace_back(u);
        }
        assert(cds.size() <= 2);
        return cds;
    }
};
// SNIPPETS_END
