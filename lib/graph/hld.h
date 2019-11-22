#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_hld
struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n) 
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
};
// SNIPPETS_END
