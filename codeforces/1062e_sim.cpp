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

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
        build_lca();
    }
    int L;
    vector<vector<int>> pa_up;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        pa[0] = 0; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        //g[v].emplace_back(u);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            //int x,y;
            //cin >> x >> y;
            //--x; --y; // to 0-based
            //add(x,y);
            int p; cin >> p;
            p--;
            add(p, _);
        }
    }
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
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
    inline bool is_ancestor(int u, int v) {
        return sta[u] <= sta[v] && fin[v] <= fin[u];
    }
    inline int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int j = L; j >= 0; j--) {
            if(!is_ancestor(pa_up[j][u], v))
                u = pa_up[j][u];
        }
        return pa_up[0][u];
    }

    void solve(int q) {
        Rmq<> rmi (sta);
        Rmq2<> rmx (sta);
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

void solve() {
    int n,q;
    cin >> n >> q;
    Tree tr(n);
    tr.solve(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
