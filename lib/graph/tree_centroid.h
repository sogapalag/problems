#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_tree_centroid
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    int root;
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

        root = centroids()[0];
        fill(pa.begin(), pa.end(), -1);
        fill(sz.begin(), sz.end(), 0);

        tim = 0; basic_dfs(root);
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
    vector<int> centroids(){
        function<void(int,int)> cdfs = [&](int u, int p) {
            sz[u] = 1;
            for (int v: g[u])if(v!=p){
                pa[v] = u;
                cdfs(v, u);
                sz[u] += sz[v];
            }
        };
        cdfs(0, -1);
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
    }
};
// SNIPPETS_END
