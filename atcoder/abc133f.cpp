#include <bits/stdc++.h>

using namespace std;

struct Graph {
    struct Edge {
        int u, v;
        int typ;
        int cost;
        Edge(int _u, int _v, int _typ, int _cost) : u(_u), v(_v), typ(_typ), cost(_cost) {}
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
        ht.resize(n);
        pos = vector<int>(n, 0);
        is_digraph = _di;
    }
    inline void add(int u, int v, int typ, int cost=1) {
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
        e.emplace_back(u, v, typ, cost);
        m++;
    }
    void input(int _m) {
        int u, v, c, d;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c >> d;
            u--; v--; c--; // input 1-based
            add(u, v, c, d);
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

    // HINT

    struct Hint {
        int id, typ, mul;
        int op;
        Hint() {}
        Hint(int _id, int _typ, int _mul, int _op) : id(_id), typ(_typ), mul(_mul), op(_op) {}
    };
    vector<vector<Hint>> ht;
    vector<bool> trk;
    vector<int> res;
    vector<int> dis;
    vector<int> sum;
    vector<int> cnt;
    void run() {
        fill(pos.begin(), pos.end(), 0);
        trk = vector<bool> (n, 0);
        res = vector<int> (100'005, 0);
        dis = vector<int> (n, 0);
        sum = vector<int> (100'005, 0);
        cnt = vector<int> (100'005, 0);
        make(0);
    }
    void make(int u) {
        for (auto& h: ht[u]) {
            if (h.op == 0) {
                res[h.id] += dis[u] * h.mul;
            } else if (h.op == 1) {
                res[h.id] += sum[h.typ] * h.mul;
            } else if (h.op == 2) {
                res[h.id] += cnt[h.typ] * h.mul;
            }
        }
        trk[u] = true;
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            if (!trk[v]) {
                dis[v] = dis[u] + e[i].cost;
                sum[e[i].typ] += e[i].cost;
                cnt[e[i].typ]++;
                make(v);
                sum[e[i].typ] -= e[i].cost;
                cnt[e[i].typ]--;
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



// offline dfs, u-v <=>  to root, u+v-2w. w=lca(u,v)
void solve() {
    int n, q;
    cin >> n >> q;
    Graph g(n, n-1);
    g.prep();
    for (int i = 0; i < q; i++) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        x--; u--; v--;
        int w = g.lca(u, v);
        g.ht[u].emplace_back(i, 0, +1, 0); // dis
        g.ht[u].emplace_back(i, x, -1, 1);// sum
        g.ht[u].emplace_back(i, x, y, 2); // cnt

        g.ht[v].emplace_back(i, 0, +1, 0); // dis
        g.ht[v].emplace_back(i, x, -1, 1);// sum
        g.ht[v].emplace_back(i, x, y, 2); // cnt

        g.ht[w].emplace_back(i, 0, -2, 0); // dis
        g.ht[w].emplace_back(i, x, +2, 1);// sum
        g.ht[w].emplace_back(i, x, -2*y, 2); // cnt
    }
    g.run();
    for (int i = 0; i < q; i++) {
        cout << g.res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
