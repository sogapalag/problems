#include <bits/stdc++.h>

using namespace std;

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
            u--;v--; // to 0-based
            add(u, v);
        }
    }
    void set_di(bool _di) {
        is_digraph = _di;
    }
    vector<bool> trk;
    vector<int> pa;
    vector<int> end;
    int tim;
    void dfs(int u) {
        trk[u] = true;
        for (int v: g[u]) {
            if (trk[v]) continue;
            dfs(v);
        }
        end[u] = tim++;
    }
    void run() {
        trk = vector<bool>(n, false);
        pa = vector<int>(n, -1);
        end = vector<int>(n, 0);
        tim = 1;
        for (int i = 0; i < n; i++) {
            if (!trk[i]) dfs(i);
        }
        vector<int> mi(n, n<<2);
        for (int u = 0; u < n; u++) {
            //cout << end[u] << "\n";
            for (int v: g[u]) {
                if (end[u] < mi[v]) {
                    mi[v] = end[u];
                    pa[v] = u;
                }
            }
        }
        for (auto& x: pa) {
            cout << (x+1) << "\n";
        }
    }
};

// topological, pa is extrem ord
void solve() {
    int n,m;
    cin >> n >> m;
    Graph g(n, n-1+m, true);
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
