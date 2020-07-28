#include <bits/stdc++.h>

using namespace std;

// should hold transitivity.
using PartialOrd = function<bool(int,int)>;
// f(x, i): x by(<) i
vector<int> get_dominating_left(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> L(n);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        // some case might need check dominating itself here
        // if not dominating itself, L[i] = i + 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        L[i] = stk.empty() ? 0 : stk.back() + 1;
        stk.push_back(i);
    }
    return L;
}
vector<int> get_dominating_right(int n, PartialOrd f) {
    assert(n > 0);
    vector<int> R(n);
    vector<int> stk;
    for (int i = n-1; i >= 0; i--) {
        // if not dominating itself, R[i] = i - 1;
        while (!stk.empty() && f(stk.back(), i)) {
            stk.pop_back();
        }
        R[i] = stk.empty() ? n-1 : stk.back() - 1;
        stk.push_back(i);
    }
    return R;
}

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
        //input(); 
    }
    int root;
    int L;
    vector<vector<int>> pa_up;
    void build() {
        for (int i = 0; i < n; i++) {
            if (pa[i] == -1) root = i;
        }
        tim = 0; basic_dfs(root);
        build_lca();
    }
    void build_lca() {
        L = 0; while ((1<<L) < n-1) L++;
        pa_up = vector<vector<int>>(L+1, vector<int>(n));
        pa[root] = root; // root-self
        for (int u: tour) {
            pa_up[0][u] = pa[u];
            for (int j = 1; j <= L; j++) {
                pa_up[j][u] = pa_up[j-1][ pa_up[j-1][u] ];
            }
        }
    }

    inline void add(int u, int v) {
        g[u].emplace_back(v);
        pa[v] = u;
        //g[v].emplace_back(u);
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
        //if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int& v: g[u]) {
            //pa[v] = u;
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

    int find(int u, int w) {
        for (int j = L; j >= 0; j--) {
            if (sz[pa_up[j][u]] < w) u = pa_up[j][u];
        }
        return pa[u];
    }
    void solve() {
    }
};

// build (door)tree y=pa[x]  : when all domi of x unlock, y be next door should be unlock
// facts:
//   1. when a subtree(i.e. domi-seg) all unlock, next door be the pa
//   2. when some pa unlock, a continous unlock(-> or <-) until next event of subtree fullfill
void solve() {
    int n,q;
    cin >> n >> q;
    --n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    auto L = get_dominating_left(n, [&](int i, int j){ return a[i]<a[j]; });
    auto R = get_dominating_right(n,[&](int i, int j){ return a[i]<a[j]; });
    Tree tr(n);
    vector<int> ls(n,-1), rs(n,-1);
    for (int i = 0; i < n; i++) {
        if (R[i] < n-1 && (L[i]==0 || a[L[i]-1] > a[R[i]+1])) tr.add(R[i]+1, i), ls[R[i]+1] = i;
    }
    for (int i = 0; i < n; i++) {
        if (L[i] > 0 && (R[i]==n-1 || a[L[i]-1] < a[R[i]+1])) tr.add(L[i]-1, i), rs[L[i]-1] = i;
    }
    tr.build();
    while (q--) {
        int s, t;
        cin >> s >> t;
        --s; --t;
        int x = (s==0 ? 0 : (s==n ? n-1 : (a[s-1]<a[s] ? s-1 : s)));
        int res;
        // note x always be one-side pa, since a[x]<a[another door of s]
        //  8 ... 3(x) s 9
        if (tr.sz[x] >= t) {
            res = x<s ? s-t : s+t; // fact2.
        } else {
        // 8(y) ... 3(x) s 5 .. 9
            // the first sz[y]>=t
            // imply x-side of y subtree all unlock, then recall fact2.
            auto y = tr.find(x, t);
            // bug below line, g[y].size might != 2
            //res = y<x ? y - (t - tr.sz[tr.g[y][1]] - 1) : y + (t - tr.sz[tr.g[y][0]]);
            // carefull y<x, not y<s
            res = y<x ? y - (t - tr.sz[rs[y]] - 1) : y + (t - tr.sz[ls[y]]);
        }
        ++res;
        cout << res << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
