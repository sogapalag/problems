#include <bits/stdc++.h>

using namespace std;

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
    vector<vector<vector<int>>> candi;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        candi.resize(L+1);
        for (int _ = 0; _ <= L; _++) {
            candi[_].resize(n);
        }
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
        g[v].emplace_back(u);
    }
    int m,q;
    void input() {
        cin >> m >> q;
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
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    vector<vector<int>> c;
    void solve() {
        // prep binary lift
        c.resize(n);
        for (int i = 0; i < m; i++) {
            int x; cin >> x; x--;
            c[x].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            while (c[i].size() > 10) {
                c[i].pop_back();
            }
        }
        auto shrink = [](auto& a){
            sort(a.begin(), a.end());
            a.erase(unique(a.begin(), a.end()), a.end());
            while (a.size() > 10) {
                a.pop_back();
            }
        };
        for (int u: tour) {
            candi[0][u] = move(c[u]);
            for (int j = 1; j <= L; j++) {
                merge(candi[j-1][u].begin(), candi[j-1][u].end(),
                      candi[j-1][ pa_up[j-1][u] ].begin(), candi[j-1][ pa_up[j-1][u] ].end(),
                      back_inserter(candi[j][u]));
                shrink(candi[j][u]);
            }
        }

        // [x..z)
        auto get_candi = [&](int x, int z){
            int dep = depth[x] - depth[z];
            vector<int> res;
            for (int j = L; j >= 0; j--) {
                if (dep>>j&1) {
                    copy(candi[j][x].begin(), candi[j][x].end(), back_inserter(res));
                    x = pa_up[j][x];
                }
            }
            shrink(res);
            return res;
        };
        while (q--) {
            int x,y,k;
            cin >> x >> y >> k;
            x--;y--;
            int z = lca(x,y);
            auto res = candi[0][z];
            auto cx = get_candi(x,z);
            auto cy = get_candi(y,z);
            merge(cx.begin(), cx.end(),cy.begin(), cy.end(),back_inserter(res));
            shrink(res);
            k = min(k, (int)res.size());
            cout << k << ' ';
            if (k) {
                for (int i = 0; i < k; i++) {
                    cout << res[i]+1 << ' ';
                }
            }cout << '\n';
        }
    }
};

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
