#include <bits/stdc++.h>

using namespace std;


// SNIPPETS_START graph_centroid_decomp_sim
// for tree use
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
            u--; v--; // input 1-based
            add(u, v);
        }
    }
    void set_di(bool _di) {
        pa = vector<int>(n, -1);
        sz = vector<int> (n, 1);
        trk = vector<bool> (n, false);
        is_digraph = _di;
    }
    
    vector<int> pa;
    vector<int> sz;
    vector<bool> trk;
    void dfs(int u) {
        trk[u] = true;
        for (int v: g[u]) if(!trk[v]){
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
            for (int v: g[u]) {
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
