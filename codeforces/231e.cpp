#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    vector<int> cnt;
    vector<bool> in_cycle;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n, -1)
        , fin(n)
        , cnt(n)
        , in_cycle(n)
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
        g[v].emplace_back(u);
    }
    void input() {
        int m; cin >> m;
        for (int _ = 0; _ < m; _++) {
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
            if (sta[v] == -1) {
                pa[v] = u;
                depth[v] = depth[u] + 1;
                basic_dfs(v);
                sz[u] += sz[v];
            } else if (sta[v] < sta[u]) {
                cnt[v] = 1; // mark high
                int x = u;
                while (x != v) {
                    in_cycle[x] = true;
                    x = pa[x];
                }
                assert(x == v);
                in_cycle[x] = true;
            }       
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

    // count path #occur-color, ans=2^k
    void solve() {
        for (int u: tour) {
            for (int v: g[u])if(pa[v]==u){
                cnt[v] += cnt[u];
            }
        }
        const int MOD = 1e9+7; 
        vector<int> pw(n+1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i-1]*2 % MOD;
        }
        int q; cin >> q;
        while (q--) {
            int x,y;
            cin >> x >> y;
            x--;y--;
            int z = lca(x,y);
            int res = cnt[x] + cnt[y] - 2*cnt[z] + (in_cycle[z]);
            cout << pw[res] << "\n";
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
