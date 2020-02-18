#include <bits/stdc++.h>

using namespace std;
using ll=long long;
#undef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(bool x) { return (x ? "T" : "F"); }
string to_string(const char* s) { return to_string((string)s); }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename V>
string to_string(V v) {
    bool f = true; string res = "[";
    for (const auto& x: v) {
        if (!f) res += ", ";
        f = false;
        res += to_string(x); } res += "]";
    return res;
}
void debug() { cerr << endl; }
template <typename H, typename... T>
void debug(H h, T... t) { cerr << " " << to_string(h); debug(t...); }
#ifdef LOCAL
#define dbg(args...) cerr<<"("<<#args<<") =", debug(args)
#else
#define dbg(args...) 2020
#endif
struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, a, high;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , a(n)
        , high(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; basic_dfs(0);
        build_lca();
        prep();
    }
    int L;
    vector<vector<int>> pa_up;
    void build_lca() {
        L = 0; while ((1<<L) < n) L++; // replace n-1 with n
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        //pa[0] = 0; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                int x = pa_up[j-1][u];
                if (x != -1)
                    pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
                else pa_up[j][u] = -1;
            }
        }
    }
    void prep() {
        vector<vector<ll>> sum(L+1, vector<ll>(n));
        for (int u: tour) {
            sum[0][u] = a[u];
            for (int j = 1; j <= L; j++) {
                int x = pa_up[j-1][u];
                if (x != -1)
                    sum[j][u] = sum[j-1][u] + sum[j-1][ pa_up[j-1][u] ];
                else sum[j][u] = sum[j-1][u];
            }
        }
dbg(L, sum);
        for (int u: tour) {
            ll x = nlim, y = slim;
            int z = u;
            for (int j = L; j >= 0 && z != -1; j--) {
                if ((1<<j) <= x && sum[j][z] <= y) {
                    x -= 1<<j;
                    y -= sum[j][z];
                    z = pa_up[j][z];
                }
            }
            // 2^l, might lack one step
            //if (z != -1) {
            //    if (1 <= x && sum[0][z] <= y) z = pa_up[0][z];
            //}
            high[u] = z;
        }
dbg(high);
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    int nlim;ll slim;
    void input() {
        cin >> nlim >> slim;
        for (auto& x: a) {
            cin >> x;
            if (x > slim) { cout << -1;exit(0); }
        }
        for (int _ = 1; _ < n; _++) {
            //int x,y;
            //cin >> x >> y;
            //--x; --y; // to 0-based
            //add(x,y);
            int p; cin >> p; p--;
            g[p].push_back(_);
        }
    }
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
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
    int dist(int u, int v) {
        return depth[u] + depth[v] - 2*depth[lca(u,v)];
    }
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    // first prep high[u]:=z, from u go up, can go [u..z) i.e. #<=nlim, sum<=slim
    // with this info, we can greedy dp.
    // since each time, we should always connect u-v while we can. (since u-v, cut u-p  is strictly better)
    //   and we always choose x s.t. high[x] go higher
    void solve() {
        vector<int> dp(n);
        // note now high means best in subtree
        for (int u = n-1; u >= 0; u--) {
            int x = -1;
            for (int v: g[u]) {
                dp[u] += dp[v];
                if (high[v] >= u) continue;
                if (x == -1 || high[x] > high[v]) {
                    x = v;
                }
            }
            if (x == -1) {
                dp[u]++;
            } else high[u] = high[x];
        }
        cout << dp[0];
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
