#include <bits/stdc++.h>

using namespace std;

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
#define dbg(args...) 2019
#endif

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
    int x;
    Node() : x(-0x3f3f3f3f) {} // DO!! identity
    Node(int _x) : x(_x) {}
    Node(const Node& _r) : x(_r.x) {}// DO!! set
    Node& operator = (const Node& _r) {// DO!! set
        x = _r.x;
        return *this;
    }
    Node& operator += (const Node& _r) {// DO!! may not communitative
        x = max(x, _r.x);
        return *this;
    }
    friend Node operator + (const Node& _lhs, const Node& _rhs) {
        return Node(_lhs) += _rhs; // derive from +=
    }
};

typedef Segtree<Node> Seg;

// edges matter
struct HLD {
    using CT = int;
    struct Edge {
        int u, v;
        CT cost;
        Edge() {}
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n;
    vector<vector<int>> g;
    vector<Edge> e;
    vector<int> sz, pa, depth, sta, fin, heavy, top, tour, edge_tour, ord;
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
        , ord(n)
        , seg(n)
        {
        tour.reserve(n);
        e.reserve(n); e.emplace_back(); // root-up-virtual
        edge_tour.reserve(n); edge_tour.emplace_back(); // virtual
        input(); 
    }

    inline void add(int u, int v, CT cost) {
        g[u].emplace_back(e.size());
        g[v].emplace_back(e.size());
        e.emplace_back(u, v, cost);
    }
    void input() {
        for (int _ = 1; _ < n; _++) {
            int x,y; CT z;
            cin >> x >> y >> z;
            --x; --y; // to 0-based
            add(x,y,z);
        }
    }
    inline int ch(int u, int i) {
        return e[i].u ^ e[i].v ^ u;
    }
    void dfs(int u, int past_edge = -1) {
        if (past_edge != -1) g[u].erase(find(g[u].begin(), g[u].end(), past_edge));
        for (int& i: g[u]) {
            int v = ch(u, i);
            pa[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, i);
            sz[u] += sz[v];
            // heavy skew left, thus chain consective on sta
            int& j = g[u][0];
            if (sz[v] > sz[ch(u,j)]) swap(i, j);
        }
    }
    // sta*tour = I, ord*edge_tour = I
    void hld(int u) {
        sta[u] = tim++;
        tour.emplace_back(u);
        for (int i: g[u]) {
            edge_tour.emplace_back(i);
            ord[i] = tim;
            int v = ch(u, i);
            top[v] = (v == ch(u, g[u][0]) ? heavy[u] = v, top[u] : v); // #h=1
            //top[v] = (sz[v] >= (sz[u]+1)/2 ? heavy[u] = v, top[u] : v); // #h<=1
            hld(v);
        }
        fin[u] = tim;
    }
    void build(int root = 0) {
        dfs(root);
        tim = 0; top[root] = root; hld(root);
dbg(sta, tour); 
dbg(ord, edge_tour);
        // seg init
        for (int i = 1; i < n; i++) {
            seg.update(i, Node(e[edge_tour[i]].cost));
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
    // [u..v], Caution: tim(0), edge_tour/cost on [1..n) alias
    void for_e_path(int u, int v, F f) {
        while (true) {
            if (sta[u] > sta[v]) swap(u, v);
            if (top[u] == top[v]) {
                if (u != v) f(sta[u]+1, sta[v]+1);
                return;
            }
            f(sta[top[v]], sta[v]+1);
            across_light(v);
        }
    }
    void for_v_sub(int u, F f, bool exclude = 0) {
        f(sta[u] + exclude, fin[u]);
    }
    void for_e_sub(int u, F f) {
        f(sta[u]+1, fin[u]);
    }
    void process_query() {
        string op;
        while (cin >> op) {
            if (op[0] == 'D') return;
            if (op[0] == 'C') {
                int i, c;
                cin >> i >> c;
                seg.update(ord[i], Node(c));
            }
            if (op[0] == 'Q') {
                int u, v;
                cin >> u >> v;
                u--; v--;
                int res = 0;
                for_e_path(u, v, [&](int l, int r){
                        res = max(res, seg.query(l,r).x);
                        });
                cout << res << "\n";
            }
        }
    }
};

void solve() {
    int n; cin >> n;
    HLD hld(n);
    hld.build();
    hld.process_query();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
