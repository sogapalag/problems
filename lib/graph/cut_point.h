#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_cut_point
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
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
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
    vector<int> pos;

    int tim;
    vector<int> low;
    vector<int> bg;
    void dfs(int u, int p=-1) {
        low[u] = bg[u] = tim++;
        int ch_cnt = 0;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            if (p == i) continue; // for un-di, not use same edge. note, can multi-edge
            int v = e[i].u ^ e[i].v ^ u;
            if (bg[v]) {
                low[u] = min(low[u], bg[v]);
            } else {
                dfs(v, i);
                low[u] = min(low[u], low[v]);
                if (bg[u] <= low[v] && p != -1) {
                    // found u
                }
                ch_cnt++;
            }
        }
        if (p == -1 && ch_cnt > 1) {
            // found u
        }
    }
    void dfs_all() {
        tim = 1;
        low.assign(n, 0);
        bg.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (!bg[i]) dfs(i);
        }
    }
};
// SNIPPETS_END
