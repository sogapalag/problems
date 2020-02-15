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

    // for u, one can note, we should pick some subsz from its(m>=n/2), add to u's another substree(which can be greedily, minimum, => actually can be 0, i.e. direct connect to u).
    //   as long as the m-n/2 <= sz <= n/2
    // but this would need some sz set track, merge.. hard to impl
    // actually we have fewer candidates.
    // let root at centroid, for any u, note m must be ubtree of u, pass the root.
    //  first we cannot cut any [u..root), by the root-cen property, m' should <= n/2
    //     except, just cut v-root, if n-sz[v]=n/2. one can see, => all u subtree of v would be yes.
    //  second, we can just cut differ sub v'-root,v'!=v.  since which sz<=n/2 for sure, so we can greedy pick max, to for the goal m'= n-sz[u] - sz[v'] <= n/2
    void solve() {
        vector<int> res(n);
        res[root] = 1;
        int mx[2] = {};
        {
            for (int v: g[root]) {
                mx[1] = max(mx[1], sz[v]);
                if (mx[0]<mx[1])swap(mx[0],mx[1]);
            }
        }
        for (int v: g[root]) {
            if (n - sz[v] == n/2) {
                for (int t = sta[v]; t < fin[v]; t++) {
                    res[tour[t]] = 1;
                }
            } else {
                int tmp = mx[0] == sz[v]? mx[1] : mx[0];
                for (int t = sta[v]; t < fin[v]; t++) {
                    int u = tour[t];
                    if (n-sz[u]-tmp <= n/2) res[u] = 1;
                }
            }
        }
        for (auto& x: res) {
            cout << x << ' ';
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
