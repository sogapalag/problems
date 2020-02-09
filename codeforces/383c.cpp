#include <bits/stdc++.h>

using namespace std;
template <typename T=int>
struct Fenwick {
    int n;
    vector<T> v;
    
    Fenwick(int size = 100005) : n(size), v(n+1, 0) {}
    inline void add(int p, T val) {
        for (; p <= n; p += (p&-p)) { v[p] += val; }
    }
    inline T query(int p) {
        T tmp = 0;
        for (; p > 0; p -= (p&-p)) { tmp += v[p]; }
        return tmp;
    }
    inline T query(int l, int r) {
        return query(r) - query(l-1);
    }
};
template <typename T>
struct RASQ {
    int n;
    Fenwick<T> diff;

    RASQ(int _n) : n(_n), diff(n) {}
    // 1-based, [l..r)
    inline void add(int l, int r, T val) {
        diff.add(l, val);
        diff.add(r, -val);
    }
    inline T query(int p) {
        return diff.query(p);
    }
};

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    vector<int> a;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n) 
        , a(n)
        {
        tour.reserve(n);
        input(); 
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

    void dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    // sta*tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int v: g[u]) {
            top[v] = (v == g[u][0] ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
    void build(int root = 0) {
        dfs(root);
        tim = 1; top[root] = root; hld(root);
    }
    inline void across_light(int& v) {
        v = pa[top[v]];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            sta[u] < sta[v] ? across_light(v) : across_light(u);
        }
        return sta[u] < sta[v] ? u : v;
    }

    using F = function<void(int,int)>; // range operation tim(0)-based [l..r)
    // [u..v]
    void for_v_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            f(max(sta[top[v]], sta[u]), sta[v]+1);
            if (top[u] == top[v]) return;
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }
    void solve(int q) {
        vector<bool> odd(n);
        for (int i = 0; i < n; i++) {
            odd[i] = depth[i]&1;
        }
        RASQ<int> ra(n);
        auto update = [&](int u, int x){
            if (odd[u]) x *= -1;
            //for_v_sub()
            ra.add(sta[u], fin[u], x);
        };
        auto query = [&](int u){
            int x = ra.query(sta[u]);
            if (odd[u]) x*=-1;
            return a[u] + x;
        };
        while (q--) {
            int op, u;
            cin >> op >> u; u--;
            if (op == 1) {
                int x; cin >> x;
                update(u, x);
            } else {
                cout << query(u) << '\n';
            }
        }
    }
};

// key, keep depth parity, update => range add
// well, no need HLD, since we only use subtree-update
void solve() {
    int n,q;
    cin >> n >> q;
    HLD hld(n);
    hld.build();
    hld.solve(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
