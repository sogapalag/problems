#include <bits/stdc++.h>

using namespace std;

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
        deg = vector<int>(n, 0);
        is_digraph = _di;
    }
    vector<int> deg;
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
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
    void dfs(int u) {
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            dfs(v);
        }
    }
    int k;
    void dele() {
        int need_del = m - (n+m+1)/2;
        if (need_del > 0) {
            int cnt = 0;
            random_shuffle(e.begin(), e.end());
            vector<int> d = deg;
            for (auto& x: e) {
                if (cnt < need_del && d[x.u]-1 >= (deg[x.u]+1)/2 && d[x.v]-1 >= (deg[x.v]+1)/2) {
                    d[x.u]--; d[x.v]--;
                    x.cost = 0;
                    cnt++;
                }
            }
            assert(cnt == need_del);
            k = (n+m+1)/2;
        } else {
            k = m;
        }
    }
    void pri() {
        cout << k << "\n";
        for (auto& x: e) {
            if (x.cost)
            cout << x.u+1 << ' ' << x.v+1 << "\n";
        }
    }
};

// random pass..
void solve() {
    int n, m;
    cin >> n >> m;
    Graph g(n, m);
    g.dele();
    g.pri();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
