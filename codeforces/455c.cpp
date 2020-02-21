#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p, diam;
    
    Dsu(int _n) { n = _n; p.resize(n); diam.resize(n); init(); }
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
        // may max dx dy
        diam[x] = max({diam[x], diam[y], (diam[x]+1)/2 + (diam[y]+1)/2 + 1});
        p[y] = x; return true;
    }
    void set(int x, int d) {
        diam[x] = d;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
    int query(int x) {
        return diam[find(x)];
    }
};

void solve() {
    int n,m,q;
    cin >> n >> m >> q;
    Dsu d(n);
    vector<vector<int>> g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        d.join(x,y);
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int dmx = -1, r = -1;
    function<void(int,int,int)> dfs = [&](int u, int p, int depth){
        if (depth > dmx) {
            dmx = depth;
            r = u;
        }
        for(int v:g[u])if(v!=p){
            dfs(v,u,depth+1);
        }
    };
    for (int i = 0; i < n; i++) {
        if (d.find(i) == i) {
            r = dmx = -1;
            dfs(i,-1,0);
            int R = r;
            r = dmx = -1;
            dfs(R, -1, 0);
            d.set(i, dmx);
        }
    }

    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x; cin >> x; x--;
            cout << d.query(x) << "\n";
        } else {
            int x,y;
            cin >> x >> y;
            x--;y--;
            d.join(x,y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
