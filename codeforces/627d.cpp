#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, a;
    int tim;
    int K, root;
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
        root = min_element(a.begin(), a.end()) - a.begin();
        tim = 0; basic_dfs(root);
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    void input() {
        cin >> K;
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

    // note a canonical form: some full + one unfull
    // a direct impl might need prep uptree.
    // here is a better impl, we let min{a} be root. this ensure uptree would never full.
    // besides, the form can actually be : some full + two unfull.
    //   since u doesn't have to be root.
    //   one can imagine if we lift the end of one unfull, it would become canonical.
    //   and since uptree never full, if choose uptree, the min-depth must be the end. which is covered.
    void solve() {
        reverse(tour.begin(), tour.end());
        vector<int> dp(n);
        auto ck = [&](int val){
            int res = 0;
            for (int u: tour){
                if (a[u] < val) {
                    dp[u] = 0;
                    continue;
                }
                int full = 1;
                int mx[2] = {};
                for (int v: g[u]){
                    if (dp[v] == sz[v]) full += dp[v];
                    else {
                        mx[1] = max(mx[1], dp[v]);
                        if (mx[1] > mx[0]) swap(mx[0], mx[1]);
                    }
                }
                res = max(res, full + mx[0] + mx[1]);
                dp[u] = full + mx[0];
            }
            return res >= K;
        };
        cout << bs_last<int>(1, 1e6+1, ck);
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
