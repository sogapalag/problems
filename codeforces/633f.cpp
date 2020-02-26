#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, a;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n)
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
        for (auto& x: a) {
            cin >> x;
        }
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
using ll=long long;
    // not necessary 3-star, can be H-shape, actually 3-star belong H
    void solve() {
        ll res = 0;
        vector<array<ll,3>> arm(n);
        // 3-star
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            arm[u][0] = a[u];
            for (int v:g[u]){
                arm[u][2] = max(arm[u][2], a[u] + arm[v][0]);
                if (arm[u][2] > arm[u][1]) swap(arm[u][2], arm[u][1]);
                if (arm[u][1] > arm[u][0]) swap(arm[u][0], arm[u][1]);
            }
            res = max(res, arm[u][0] + arm[u][1] + arm[u][2] - 2*a[u]);
        }
        vector<ll> up(n);
        up[0] = a[0];
        for (int u: tour) {
            res = max(res, arm[u][0] + arm[u][1] + up[u] - 2*a[u]);
            for (int v:g[u]){
                ll tmp = a[u]+arm[v][0] == arm[u][0] ? arm[u][1] : arm[u][0];
                up[v] = a[v] + max(tmp, up[u]);
            }
        }

        // a max chain sub u, not necessary pass u.
        vector<ll> dnbest(n);
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            dnbest[u] = a[u];
            dnbest[u] = max(dnbest[u], arm[u][0] + arm[u][1] - a[u]);
            for (int v:g[u]) {
                dnbest[u] = max(dnbest[u], dnbest[v]);
            }
        }
        // a max chain above v, i.e. we iter u-v as a cut
        vector<ll> upbest(n);
        for (int u: tour) {
            for (int v:g[u]) {
                ll tmp = a[u]+arm[v][0] == arm[u][0] ? arm[u][1] : arm[u][0];
                upbest[v] = max(upbest[v], upbest[u]);
                // pass u, 1-up, 1-dn
                upbest[v] = max(upbest[v], tmp + up[u] - a[u]);
                // pass u, 2-dn, note we exclude v.
                int i = 0;
                for (; i < 3; i++) {
                    if (a[u] + arm[v][0] == arm[u][i]) break;
                }
                ll sum = arm[u][0]+arm[u][1]+arm[u][2];
                if (i >= 2) sum -= arm[u][2];
                else sum -= arm[u][i];
                upbest[v] = max(upbest[v], sum - a[u]);
            }
            // maintain pref/suff max, since upb[v] can be some dnb[v']
            int m = g[u].size();
            vector<ll> pref(m + 1);
            for (int i = 0; i < m; i++) {
                int v = g[u][i];
                pref[i+1] = max(pref[i], dnbest[v]);
            }
            ll suff = 0;
            for (int i = m-1; i >= 0; i--) {
                int v = g[u][i];
                upbest[v] = max(upbest[v], max(suff, pref[i]));
                suff = max(suff, dnbest[v]);

                // maxi
                res = max(res, dnbest[v] + upbest[v]);
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
