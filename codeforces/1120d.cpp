#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> p;
    
    Dsu(int _n) { n = _n; p.resize(n); init(); }
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
        p[y] = x; return true;
    }
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    vector<int> a;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        for (auto& x: a) {
            cin >> x;
        }
        for (int _ = 1; _ < n; _++) {
            int x,y;
            cin >> x >> y;
            --x; --y; // to 0-based
            add(x,y);
        }
    }
    void basic_dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            sz[u] += sz[v];
        }
        ++sz[u];
        fin[u] = tim;
    }

    void solve() {
        vector<int> l(n, n), r(n);
        int leaf = 0;
        for (int u: tour)if(sz[u]==1) l[u]=r[u] = ++leaf;
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (int v: g[u]) {
                l[u] = min(l[u], l[v]);
                r[u] = max(r[u], r[v]);
            }
            //kr.add(l[u]-1, r[u], a[u], u);
        }
        vector<int> id(n);
        iota(id.begin(), id.end(), 0);
        sort(id.begin(), id.end(), [&](auto& u, auto& v){
            return a[u] < a[v];
        });
        Dsu d(leaf+1);
        long long tot = 0;
        int i = 0;
        vector<int> res; // not MST, are could in MST
        // so process equals same time.
        while (i < n) {
            int j = i;
            while (j < n && a[id[j]] == a[id[i]]) {
                j++;
            }
            for (int k = i; k < j; k++) {
                int u = id[k];
                if (!d.check(l[u] - 1, r[u])) {
                    res.push_back(u);
                }
            }
            for (int k = i; k < j; k++) {
                int u = id[k];
                if (d.join(l[u]-1, r[u])) tot += a[u];
            }
            i = j;
        }
        sort(res.begin(), res.end());
        cout << tot << ' ' << res.size() << "\n";
        for (auto& x: res) {
            cout << x + 1 << ' ';
        }
    }
};

// there is dp method, note under any subtree u, cannot be >= 2 holes(leaf not covered). otherwise cannot distinguish. and under root, 0 holes
void solve() {
    int n; cin >> n;
    Tree tr(n); tr.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
