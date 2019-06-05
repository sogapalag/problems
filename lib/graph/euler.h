#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_euler
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

    Graph(int _n) : n(_n), m(0){
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
        if (is_digraph) {
            indeg = vector<int>(n, 0);
            outdeg = vector<int>(n, 0);
        } else {
            deg = vector<int>(n, 0);
        }
    }
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            deg[u]++; deg[v]++;
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
    vector<int> deg;
    vector<int> indeg;
    vector<int> outdeg;
    vector<int> path;
    // Hierholzer’s
    pair<int, int> _euler_entry_un();
    pair<int, int> _euler_entry_di();
    pair<int, int> euler_entry();
    void euler_dfs(int u);
    int euler_run();
};

void Graph::euler_dfs(int u) {
    for (; pos[u] < g[u].size(); pos[u]++) {
        int i = g[u][pos[u]];
        if (e[i].cost) {
            e[i].cost--;
            int v = e[i].u ^ e[i].v ^ u;
            euler_dfs(v);
        }
    }
    // a reversed chain, must be end time. or alternate method.
    // consider 1->2->2->3
    path.emplace_back(u);
}
pair<int, int> Graph::_euler_entry_un() {
    assert(!is_digraph);
    int odd_cnt = 0;
    int start = 0;
    for (int u = 0; u < n; u++) {
        if (deg[u] & 1) {
            odd_cnt++;
            start = u;
        }
    }
    if (odd_cnt > 2)
        return {-1, -1};
    assert(odd_cnt != 1);
    if (odd_cnt)
        return {1, start};
    return {0, start};
}

// -1, no path
// 0, cycle
// 1, semi-euler, aka, path
pair<int, int> Graph::_euler_entry_di() {
    assert(is_digraph);
    int odd_cnt = 0;
    int start = 0;
    for (int u = 0; u < n; u++) {
        if (indeg[u] == outdeg[u])
            continue;
        if (outdeg[u] > indeg[u] + 1)
            return {-1, -1};
        if (indeg[u] > outdeg[u] + 1)
            return {-1, -1};
        odd_cnt++;
        if (outdeg[u] == indeg[u] + 1)
            start = u;
    }
    if (odd_cnt > 2)
        return {-1, -1};
    assert(odd_cnt != 1);
    if (odd_cnt)
        return {1, start};
    return {0, start};
}
int Graph::euler_run() {
    int flag, start;
    tie(flag, start) = is_digraph? _euler_entry_di() : _euler_entry_un();
    if (flag < 0)
        return -1;
    path.clear();
    path.reserve(m+1);
    euler_dfs(start);
    // not connected
    if ((int) path.size() < m+1)
        return -1;
    return flag;
}
// SNIPPETS_END
