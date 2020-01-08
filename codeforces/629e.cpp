#include <bits/stdc++.h>

using namespace std;

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    vector<double> dn, up;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n)
        , dn(n)
        , up(n)
        {
        tour.reserve(n);
        input(); 
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
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
        tim = 0; top[root] = root; hld(root);
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

    int get_dist(int u, int v) {
        int sum = 0;
        for_v_path(u,v,[&](int l, int r){sum+=r-l;});
        return sum - 1;
    }

    void prep_dp(){
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (int v: g[u]) {
                dn[u] += dn[v];
            }
            dn[u] += sz[u] - 1;
        }
        for (int u: tour) {
            for (int v: g[u]) {
                up[v] = up[u] + dn[u] - (dn[v] + sz[v]);
                up[v] += n - sz[v];
            }
        }
    }
    
    int get_w(int u, int v) {
        while (top[v] != top[u]) {
            v = top[v];
            if (pa[v] == u) return v;
            else v = pa[v];
        }
        return tour[sta[u] + 1];
    }

    void solve(int m) {
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            if (sta[u] > sta[v]) swap(u,v);
            double sum = 0;
            double tmp = get_dist(u, v) + 1;
            if (lca(u,v) == u) {
                // need get u's direct child to v, binary lifting could be easier
                int w = get_w(u, v);
                assert(pa[w] == u);
                sum += dn[v] * (n - sz[w]);
                sum += (up[w] - (n-sz[w])) * sz[v];
                sum /= sz[v];
                sum /= (n - sz[w]);
            } else {
                sum += dn[v] * sz[u];
                sum += dn[u] * sz[v];
                sum /= sz[u];
                sum /= sz[v];
            }
            sum += tmp;
            cout << sum << "\n";
        }
    }
};

// widely use trick: sum pi pj (x + y) = sum (pi x) pj + sum pi (pj y)
void solve() {
    int n, m;
    cin >> n >> m;
    HLD hld(n);
    hld.build();
    hld.prep_dp();
    hld.solve(m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(10);
    solve();
    cout << endl;
}
