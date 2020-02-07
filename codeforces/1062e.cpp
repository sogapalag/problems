#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 17; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] < raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return raw[query_id(l, r)];
    }
};
template <typename T=int>
struct Rmq2 {
    vector<T> raw;
    static const int LOG = 17; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq2(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return raw[x] > raw[y] ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return raw[query_id(l, r)];
    }
};

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
    vector<int> depth;
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
            if (v != pa) depth[v]=depth[u]+1,_dfs(v, u);
        }
        nd[u] = tim++;
    }
    inline bool _is_ancestor(int u, int v) {
        return bg[u] <= bg[v] && nd[u] >= nd[v];
    }
    inline int lca(int u, int v);

    void solve(int q) {
        Rmq<> rmi (bg);
        Rmq2<> rmx (bg);
        auto lca_by_range = [&](int l, int r){
            if (l >= r) return -1;
            return lca(rmi.query_id(l,r), rmx.query_id(l,r));
        };
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--;
            int u = rmi.query_id(l, r);
            int v = rmx.query_id(l, r);
            int z0;
            {
                z0 = lca_by_range(l, u);
                int t = lca_by_range(u+1, r);
                if (z0 == -1) z0 = t;
                else if (t != -1) z0 = lca(z0, t);
            }
            int z1;
            {
                z1 = lca_by_range(l, v);
                int t = lca_by_range(v+1, r);
                if (z1 == -1) z1 = t;
                else if (t != -1) z1 = lca(z1, t);
            }

            if (depth[z0] < depth[z1]) {
                cout << v+1 << ' ' << depth[z1] << '\n';
            } else {
                cout << u+1 << ' ' << depth[z0] << '\n';
            }
        }
    }
};
void Graph::prep(int root=0) {
    k = 32 - __builtin_clz(n);
    for (int j = 0; j <= k; j++) {
        up[j].resize(n);
    }
    bg = vector<int>(n, 0);
    nd = vector<int>(n, 0);
    depth = vector<int>(n, 0);
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

// key, acens iff in_z<=in_x<=out_z
void solve() {
    int n,q;
    cin >> n >> q;
    Graph g(n); g.set_di(true);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        g.add(p, i);
    }
    g.prep();
    g.solve(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
