#include <bits/stdc++.h>

using namespace std;

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
        //auto cs = centroids();
        //if (cs.size() > 1) {
        //    cout << "-1"; exit(0);
        //}
        //root = cs[0];
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

    // obvious the tree has some balance structure
    //  centroid can be one candidate.
    //  oen exception, there could be some vert-path from real-root to centroid.
    void solve() {
        {// check centroid
            bool yes = true;
            vector<int> deg(n, -1);
            for (int u: tour) {
                int d = depth[u];
                int x = g[u].size();
                if (deg[d] == -1) {
                    deg[d] = x;
                } else if (deg[d] != x) {
                    yes = false; break;
                }
            }
            if(yes) {
                cout << root+1; return;
            }
        }

        // find vert
        vector<int> vert(n, -1);
        for (int u: vector<int>(tour.rbegin(), tour.rend())) {
            int x = g[u].size();
            if (x == 0) {
                vert[u] = u;
            } else if (x == 1) {
                int v = g[u][0];
                vert[u] = vert[v];
            }
        }
        // note the only solution is flip some vert(which depth must be unique).
        vector<int> uniq(n, -1);
        for (int v: g[root]) {
            int x = vert[v];
            if (x != -1) {
                int d = depth[x];
                if (uniq[d] == -1) uniq[d] = x;
                else uniq[d] = -2;
            }
        }
        int z = -1;
        for (int x: uniq) if (x >= 0) z = x;
        if (z == -1) {
            cout << -1; return;
        }

        {
            int Z = z;
            // flip(exclude) the vert
            vector<bool> trk(n);
            while (z != root) {
                trk[z] = true;
                z = pa[z];
            }
            // check again
            bool yes = true;
            vector<int> deg(n, -1);
            for (int u: tour) if(!trk[u]){
                int d = depth[u];
                int x = g[u].size();
                if (deg[d] == -1) {
                    deg[d] = x;
                } else if (deg[d] != x) {
                    yes = false; break;
                }
            }
            if(yes) {
                cout << Z+1;
            } else {
                cout << -1;
            }
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
