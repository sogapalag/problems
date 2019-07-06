#include <bits/stdc++.h> = x.u, v = x.v, c = x.cost;
            if (depth[u] > depth[v]) swap(u, v);
            change_path(u, -c);
            change_path(v, c)

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
        depth = vector<int>(n, 0);
        trk = vector<bool>(n, false);
        lowleaf.resize(n);
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
        int u, v, c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c;
            u--; v--; // input 1-based
            add(u, v, c);
        }
    }
    vector<int> pos;
    vector<bool> trk;
    vector<int> depth;
    vector<vector<int>> lowleaf;
    int root=0;
    void dfs(int u) {
        trk[u] = true;
        if (u!=root && deg[u] == 1)
            lowleaf[u].emplace_back(u);
        for (; pos[u] < g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (!trk[v]) {
                depth[v] = depth[u] + 1;
                dfs(v);
                lowleaf[u].emplace_back(lowleaf[v][0]);
            }
        }
    }
    bool check() {
        for (auto& x: deg) {
            if (x==2) return false;
        }
        return true;
    }
    vector<Edge> mod;
    
    void change_path(int u, int c) {
        if (u == root) return;
        if (deg[u] == 1) {
            mod.emplace_back(root, u, c);
            return;
        }
        mod.emplace_back(root, lowleaf[u][0], c/2);
        mod.emplace_back(root, lowleaf[u][1], c/2);
        mod.emplace_back(lowleaf[u][0], lowleaf[u][1], -c/2);
    }
    void run() {
        if (!check()) {
            cout << "NO" << "\n";
            return;
        }
        // choose a leaf as root
        for (int i = 0; i < n; i++) {
            if (deg[i] == 1) {
                root = i; break;
            }
        }
        dfs(root);
        for (auto& x: e) {
            int u = x.u, v = x.v, c = x.cost;
            if (depth[u] > depth[v]) swap(u, v);
            change_path(u, -c);
            change_path(v, c);
        }
        cout << "YES" << "\n";
        cout << mod.size() << "\n";
        for (auto& x: mod) {
            int u = x.u+1, v = x.v+1, c = x.cost;
            cout << u << ' ' << v << ' ' << c << "\n";
        }
    }
};

// for simplicity, and wlog, choose leaf r as root
// for edge u-v, wlog, suppose depth u<v
// then u-v +x  <=>  r-u  -x,  r-v  +x
// then r-u +x  <=>  r-l0  +x/2, r-l1  +x/2,  l0-l1 -x/2;  where l0,l1 are u's differet subtree's leaves
void solve() {
    int n; cin >> n;
    Graph g(n, n-1);
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
