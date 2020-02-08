#include <bits/stdc++.h>

using namespace std;

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour;
    int tim;
    vector<int> a;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        //, depth(n)
        //, sta(n)
        //, fin(n)
        , a(n)
        {
        //tour.reserve(n);
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
        //sta[u] = tim++;
        //tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            //depth[v] = depth[u] + 1;
            basic_dfs(v);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
        ++sz[u];
        //fin[u] = tim;
    }

using ll=long long;
    vector<map<int,int>> cnt;
    vector<map<int,ll>> sum;
    vector<ll> res;
    void dfs(int u) {
        bool is_first = true;
        for (int v: g[u]) {
            dfs(v);
            if (is_first) {
                cnt[u] = move(cnt[v]);
                sum[u] = move(sum[v]);
                is_first = false;
            } else {//merge
                for (auto& _: cnt[v]) {
                    int x,y;
                    tie(x,y) = _;
                    auto& f = cnt[u][x];
                    sum[u][f] -= x;
                    sum[u][f += y] += x;
                }
            }
        }
        int x = a[u];
        auto& f = cnt[u][x];
        sum[u][f] -= x;
        sum[u][f+=1] += x;

        res[u] = sum[u].rbegin()->second;
    }

    void solve() {
        cnt.resize(n);
        sum.resize(n);
        res.resize(n);
        dfs(0);
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
