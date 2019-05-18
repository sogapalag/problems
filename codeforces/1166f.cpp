#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    vector<set<int>> r;
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x].size() < r[y].size()) swap(x, y);
        p[y] = x;
        for (int item: r[y]) {
            r[x].emplace(item);
        }
        r[y].clear();
        return true;
    }
    inline void ins_nei(int x, int y) {
        r[find(x)].emplace(y);
        r[find(y)].emplace(x);
    }
    inline bool check(int x, int y) {
        return find(x) == find(y) || r[find(x)].count(y);
    }
};

// r[] store component asides, achievable neiber of compnents.
void solve() {
    int n, m, c, q;
    cin >> n >> m >> c >> q;
    vector<map<int, int>> g(n);
    Dsu dsu(n);
    auto add = [&](int u, int v, int _c){
        auto it = g[u].find(_c);
        if (it != g[u].end()) {
            dsu.join(v, it->second);
        }
        it = g[v].find(_c);
        if (it != g[v].end()) {
            dsu.join(u, it->second);
        }
        g[u][_c] = v;
        g[v][_c] = u;
        dsu.ins_nei(u, v);
    };
    auto ck = [&](int u, int v){
        return dsu.check(u, v);
    };
    while (m--) {
        int u, v, _c;
        cin >> u >> v >> _c;
        u--; v--;
        add(u, v, _c);
    }
    while (q--) {
        char op;
        int u, v, _c;
        cin >> op >> u >> v;
        u--; v--;
        if (op == '+') {
            cin >> _c;
            add(u, v, _c);
        }else{
            if (ck(u, v)) {
                cout << "Yes\n";
            }else{
                cout << "No\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
