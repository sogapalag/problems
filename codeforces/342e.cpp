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
        auto root = centroids()[0];
        fill(pa.begin(), pa.end(), -1);
        fill(sz.begin(), sz.end(), 0);
        tim = 0; basic_dfs(root);
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
        cin >> q; 
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
    void simple_dfs(int u, int p) {
        for (int v: g[u])if(v!=p) {
            pa[v] = u;
            simple_dfs(v,u);
            sz[u] += sz[v];
        }
        ++sz[u];
    }
    vector<int> centroids(){
        simple_dfs(0, -1);
        vector<int> cds;
        for (int u = 0; u < n; u++) {
            bool yes = true;
            for (int v: g[u]) {
                if (v!=pa[u]) yes &= sz[v] <= n/2;
            }
            yes &= n-sz[u] <= n/2;
            if (yes) cds.emplace_back(u);
        }
        assert(cds.size() <= 2);
        return cds;
    }

    int q;
    void solve() {
        while (q--) {
            int op, u;
            cin >> op >> u; u--;
        }
    }
};

struct CentroidDecompositionAutomaton {
    int n;
    vector<vector<int>> g;
    vector<bool> trk;
    int tim;
    vector<int> sz, sta, fin, pa, depth, dn, tour;
    vector<int> centroids_tour;
#define __limit_loop for(int v:g[u])if(!trk[v]&&v!=p)
#define __adj_loop for(int v:g[u])if(v!=p)
    CentroidDecompositionAutomaton(int _n)
        : n(_n)
        , g(n)
        , trk(n, false)
        , sz(n)
        , sta(n)
        , fin(n)
        , pa(n)
        , depth(n)
        , dn(n, 1<<29)
    {
        tour.reserve(n);
        input();
        tim = 0; basic_dfs(0);
        build_lca();
        // reuse for cen_pa
        fill(pa.begin(), pa.end(), -1);
        run();
    }
    // LCA
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
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u])if(v!=pa[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            //sz[u] += sz[v];
        }
        //++sz[u];
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
    // END LCA
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        cin >> q;
        int u, v;
        for (int _ = 1; _ < n; _++) {
            cin >> u >> v;
            u--;v--; // to 0-based
            add(u, v);
        }
    }
    int SZ, CEN;
    void find_centroid(int u, int p) {
        sz[u] = 1;
        bool yes = true;
        __limit_loop {
            find_centroid(v, u);
            yes &= sz[v] <= SZ/2;
            sz[u] += sz[v];
        }
        yes &= SZ - sz[u] <= SZ/2;
        if (yes) CEN = u;
    }
    void recalc_sz(int u, int p) {
        sz[u] = 1;
        __limit_loop {
            recalc_sz(v, u);
            sz[u] += sz[v];
        }
    }
    void get_centroids_tour(int u, int p) {
        find_centroid(u, -1);
        trk[u=CEN] = true;
        pa[u] = p;
        centroids_tour.push_back(u);
        recalc_sz(u, -1);
        __limit_loop {
            SZ = sz[v];
            get_centroids_tour(v, u);
        }
    }

    void run() {
        centroids_tour.reserve(n);
        SZ = n; get_centroids_tour(0,-1);
        //fill(trk.begin(), trk.end(), false);
        //for (int u: centroids_tour) {
        //    solve(u);
        //    trk[u] = true;
        //}
    }

    // merge lca/cda lib
    // build lca on any root(e.g. 0)
    // build cda.
    // update/query follow cda's pa, while dist info by lca.
    int q;
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    void update(int u) {
        int x = u;
        while (x != -1) {
            dn[x] = min(dn[x], dist(x, u));
            x = pa[x];
        }
    }
    int query(int u) {
        int x = u;
        int res = 1<<29;
        while (x != -1) {
            res = min(res, dn[x] + dist(x, u));
            x = pa[x];
        }
        return res;
    }
    void solve() {
        update(0);
        while (q--) {
            int op,u;
            cin >> op >> u; u--;
            if (op == 1) update(u);
            else cout << query(u) << '\n';
        }
    }

    // Caution: use __limit_loop to dfs
    //void solve(int u) {
    //    // 
    //}
#undef __limit_loop
#undef __adj_loop
};

void solve() {
    int n; cin >> n;
    CentroidDecompositionAutomaton cda(n); cda.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
