#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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

    inline ll c2(ll x) { return x*(x-1)/2; }
    // note path(a,b) would cut tree into forests, then each tree, c2(sz)
    // consider each subtree(/uptree) contribution. when it be cut into?
    void solve() {
        vector<ll> sum(n);
        for (int i = 0; i < n; i++) {
            for (int v:g[i]) sum[i] += c2(sz[v]);
            if (pa[i]!=-1) sum[i] += c2(n-sz[i]);
        }
        ll res = 0;
        for (int i = 0; i < n; i++) {
            for (int v: g[i]) {
                ll up = c2(n-sz[v]);
                ll dn = c2(sz[v]);
                ll x = up - (sum[i] - dn); // \E a path pass i
                res += x*dn; // subtree v,
                ll y = dn - (sum[v] - up); // \E a path pass v
                res += y*up; // uptree i
            }
        }
        cout << res;
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
