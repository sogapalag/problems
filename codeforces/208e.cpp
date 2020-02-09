#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct FrontVector {
    vector<T> a;
    FrontVector() {}
    FrontVector(int n, const T& x = T()) : a(n, x) {}

    void push_front(T x) {
        a.push_back(x);
    }
    void pop_front() {
        a.pop_back();
    }
    T& front() {
        return a.back();
    }
    bool empty() const {
        return a.empty();
    }
    size_t size() { return a.size(); }
    T& operator[](size_t i){
        return a[size()-i-1];
    }
};

struct Tree {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, tour, arm;
    int tim;
    Tree(int _n) : n(_n)
        , g(n)
        , sz(n)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , arm(n)
        {
        tour.reserve(n);
        input(); 
        tim = 0; //basic_dfs(root);
        for (auto& r: roots) {
            basic_dfs(r);
        }
        build_lca();
    }
    int L;
    vector<vector<int>> pa_up;
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        //pa[0] = 0; // root-self
        for (auto& r: roots) {
            pa[r] = r;
        }
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }

    vector<int> roots;
    inline void add(int u, int v) {
        g[u].emplace_back(v);
        //g[v].emplace_back(u);
    }
    void input() {
        for (int i = 0; i < n; i++) {
            int p; cin >> p; p--;
            if (p < 0) roots.push_back(i);
            else add(p, i);
        }
        //for (int _ = 1; _ < n; _++) {
        //    int x,y;
        //    cin >> x >> y;
        //    --x; --y; // to 0-based
        //    add(x,y);
        //}
    }
    void basic_dfs(int u) {
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            basic_dfs(v);
            arm[u] = max(arm[u], arm[v] + 1);
            sz[u] += sz[v];
            // skew
            if (arm[v] > arm[g[u][0]]) swap(v, g[u][0]);
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
    int goup(int u, int step) {
        for (int j = L; j >= 0; j--) {
            if (step>>j&1) u = pa_up[j][u];
        }
        return u;
    }

    vector<vector<pair<int, int>>> evs;
    vector<FrontVector<int>> cnt; 
    vector<int> res;
    void dfs(int u) {
        bool is_first = true;
        for (int v: g[u]) {
            dfs(v);
            if (is_first) {
                is_first = false;
                cnt[u] = move(cnt[v]);
            } else {
                int m = cnt[v].size();
                for (int i = 0; i < m; i++) {
                    cnt[u][i] += cnt[v][i];
                }
            }
        }
        cnt[u].push_front(1);
        for (auto& _: evs[u]) {
            int k,i;
            tie(k,i) = _;
            res[i] = cnt[u][k];
        }
    }
    // offline small-to-large, watch out forest
    void solve() {
        evs.resize(n);
        cnt.resize(n);
        int q; cin >> q;
        res.resize(q);
        for (int i = 0; i < q; i++) {
            int v,k;
            cin >> v >> k; v--;
            int u = goup(v, k);
            if (depth[v] - depth[u] != k) res[i] = 1;
            else {
                evs[u].emplace_back(k, i);
            }
        }
        for (auto& r: roots) {
            dfs(r);
        }
        for (auto& x: res) {
            cout << x-1 << ' ';
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
