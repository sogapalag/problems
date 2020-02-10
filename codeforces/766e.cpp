#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int L = 20; 
using Freq = array<int,L>;
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, a;
    int tim;
    vector<Freq> cnt;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n)
        , cnt(n)
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

    void solve() {
        ll res = 0;
        fill(sz.begin(), sz.end(), 0);
        // well bit-independent, by iter L first, only O(n) space
        for (int _ = n-1; _ >= 0; _--) {
            int u = tour[_];
            int x = a[u];
            for (int i = L-1; i >= 0; i--) {
                if (x>>i&1) cnt[u][i]++;
            }
            res += x;
            sz[u]++;
            for (int v: g[u]) {
                // convo
                for (int i = L-1; i >= 0; i--) {
                    res += cnt[u][i] * (1ll<<i) * (sz[v] - cnt[v][i]);
                    res += cnt[v][i] * (1ll<<i) * (sz[u] - cnt[u][i]);
                }
                // merge
                for (int i = L-1; i >= 0; i--) {
                    if (x>>i&1) cnt[u][i] += sz[v] - cnt[v][i];
                    else cnt[u][i] += cnt[v][i];
                }
                sz[u] += sz[v];
            }
        }
        cout << res;
    }
};

// key: focus one bit
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
