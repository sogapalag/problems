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
        sta = vector<int>(n, 0);
        outdeg =vector<int> (n,0);
        tim=1;
    }
    int tim;
    vector<int> sta;
    vector<int> outdeg;
    void dfs(int u, int p) {
        sta[u] = tim++;
        for (int v: g[u]) if(v!=p){
            if (!sta[v]) {
                dfs(v, u);
                if (outdeg[v]&1) {
                    outdeg[v]++;
                    cout << v+1 << ' ' << u+1 << "\n";
                } else {
                    outdeg[u]++;
                    cout << u+1 << ' ' << v+1 << "\n";
                }
            } else if (sta[u] > sta[v]){
                cout << u+1 << ' ' << v+1 << "\n";
                outdeg[u]++;
            }
        }
    }
    void run() {
        if (m&1) {
            cout << -1; return;
        }
        dfs(0,-1);
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    Graph g(n,m);
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
