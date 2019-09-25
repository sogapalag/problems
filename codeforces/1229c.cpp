#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

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
        outdeg[u]++;
        indeg[v]++;
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
            if (u>v) swap(u,v);
            add(u, v);
        }
    }
    void set_di(bool _di) {
        is_digraph = _di;
        indeg = vector<int> (n,0);
        outdeg = vector<int> (n,0);
    }
    vector<int> indeg, outdeg;
    
    ll mid_at(int u){
        return (ll)indeg[u]*outdeg[u];
    }
    void run() {
        ll res = 0;
        for (int i = 0; i < n; i++) {
            res += mid_at(i);
        }
        cout << res << "\n";
        int q; cin >> q;
        while (q--) {
            int x; cin >> x; x--;
            res -= mid_at(x);
            for (int v: g[x]) {
                res -= mid_at(v);
                add(v, x); indeg[v]--; outdeg[x]--;
                res += mid_at(v);
            }
            g[x].clear();
            res += mid_at(x);
            cout << res << "\n";
        }
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    Graph g(n,m, true);
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
