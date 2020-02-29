#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    vector<int> P,Q;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , P(n)
        , Q(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
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
        for (int i = 0; i < n; i++) {
            cin >> P[i] >> Q[i];
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

    // there're 3 part, on path (*1), on subtree of v (*0), else (*2*0.5=*1)
    //   i.e. (n-sz[v])
    // res = sum_{u,v} (n - sz[v])p[u]q[v]
    void solve() {
        vector<double> dn(n), up(n);
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            for (int v:g[u]){
                dn[u] += dn[v];
            }
            dn[u] += sz[u] * 1ll * Q[u];
        }
        for (int u:tour){
            for (int v:g[u]){
                up[v] = up[u] + (dn[u] - dn[v] - sz[u]*1ll*Q[u]) + (n-sz[v]) * 1ll * Q[u];
            }
        }
        double res = 0, sp=0, sq=0;
        for (int u = 0; u < n; u++) {
            double sum = up[u] + (dn[u] - sz[u]*1ll*Q[u]);
            sum += n*1ll*Q[u];
            res += P[u] * sum;
            sp += P[u];
            sq += Q[u];
        }

        res /= sp*sq;
        res = n - res;
        cout << fixed << setprecision(10) << res;
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
