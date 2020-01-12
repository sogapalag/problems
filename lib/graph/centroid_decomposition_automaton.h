#include <bits/stdc++.h>

using namespace std;

struct CentroidDecompositionAutomaton {
    int n;
    vector<vector<int>> g;
    vector<bool> trk;
    vector<int> sz;
    vector<int> centroids_tour;
#define __limit_loop for(int v:g[u])if(!trk[v]&&v!=p)
#define __adj_loop for(int v:g[u])if(v!=p)
    CentroidDecompositionAutomaton(int _n)
        : n(_n)
        , g(n)
        , trk(n, false)
        , sz(n)
    {
        input();
    }
    inline void add(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
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
        fill(trk.begin(), trk.end(), false);
        for (int u: centroids_tour) {
            solve(u);
            trk[u] = true;
        }
    }

    // Caution: use __limit_loop to dfs
    void solve(int u) {
        // 
    }
#undef __limit_loop
#undef __adj_loop
};
