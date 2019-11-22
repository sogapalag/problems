#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    const T ID;
    vector<T> v; //tree
    
    Segtree(int _n = 100005) : n(_n), sz_v(n<<1), ID() {
        v.resize(sz_v);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            // v[i+n] = raw[i];
        }
        build();
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            v[i] = v[i<<1] + v[i<<1|1];
        }
    }
    inline void update(int p, T val) {
        assert(p>=0);
        for (v[p += n] = val; p >>= 1;) {
            v[p] = v[p<<1] + v[p<<1|1];
        }
    }
    inline T query(int l, int r) {
        T resl(ID), resr(ID);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { resl = resl + v[l++]; }
            if (r & 1) { resr = v[--r] + resr; }
        }
        return resl + resr;
    }
    // Note only when range-assign, single-access not interfere. e.g max
    //inline void update(int l, int r, T val) {
    //    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
    //        if (l & 1) { v[l++] = val; }
    //        if (r & 1) { v[--r] = val; }
    //    }
    //}
    //inline T query(int p){
    //    T res(ID);
    //    for (p += n; p > 0; p >>= 1) { res += v[p]; }
    //    return res;
    //}
};

struct Node {// monoid
    int x, i;
    Node() : x(0x3f3f3f3f) {} // DO!! identity
    Node(int _x, int _i) : x(_x), i(_i) {} // DO!! identity
    Node(const Node& _r) : x(_r.x), i(_r.i) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        i = _r.i;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        if (x > _r.x || (x == _r.x && i > _r.i)) {
            x = _r.x;
            i = _r.i;
        }
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

struct HLD {
    int n;
    vector<vector<int>> g;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour;
    int tim;
    Seg seg;
    HLD(int _n) : n(_n)
        , g(n)
        , sz(n, 1)
        , pa(n, -1)
        , depth(n)
        , sta(n)
        , fin(n)
        , heavy(n, -1)
        , top(n) 
        , seg(n)
        {
        tour.reserve(n);
        input(); 
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

    void dfs(int u) {
        if (pa[u] != -1) g[u].erase(find(g[u].begin(), g[u].end(), pa[u]));
        for (int& v: g[u]) {
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }
    // sta*tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int v: g[u]) {
            top[v] = (v == g[u][0] ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
    void build(int root = 0) {
        dfs(root);
        tim = 0; top[root] = root; hld(root);
        for (int i = 0; i < n; i++) {
            seg.update(i, Node(1, i));
        }
    }
    inline void across_light(int& v) {
        v = pa[top[v]];
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            sta[u] < sta[v] ? across_light(v) : across_light(u);
        }
        return sta[u] < sta[v] ? u : v;
    }

    using F = function<void(int,int)>; // range operation tim(0)-based [l..r)
    // [u..v]
    void for_v_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            f(max(sta[top[v]], sta[u]), sta[v]+1);
            if (top[u] == top[v]) return;
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }
    void process_query(int q) {
        while (q--) {
            int op; cin >> op;
            if (op == 0) {
                int u; cin >> u;
                u--;
                u = sta[u];
                int old = seg.v[n+u].x;
                seg.update(u, Node(old^1, u));
            } else {
                int u; cin >> u;
                u--;
                Node res = {1, -1};
                for_v_path(0, u, [&](int l, int r){
                        res += seg.query(l, r);
                        });
                int ans = res.x==1 ? -1 : tour[res.i] + 1;
                cout << ans << "\n";
            }
            //for (int _ = 0; _ < n; _++) {
            //    cout << seg.v[_].x << ' ';
            //}cout<<"\n";
            //for (int _ = 0; _ < n; _++) {
            //    cout << seg.v[_].i << ' ';
            //}cout<<"\n";
            //for (int _ = 0; _ < n; _++) {
            //    cout << seg.v[n+_].x << ' ';
            //}cout<<"\n";
            //for (int _ = 0; _ < n; _++) {
            //    cout << seg.v[n+_].i << ' ';
            //}cout<<"\n";
        }
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    hld.build();
    hld.process_query(q);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
