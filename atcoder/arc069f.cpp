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

struct Graph {
    struct Edge {
        int u, v;
        int cost;
        Edge(int _u, int _v, int _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    vector<vector<int>> g;
    vector<Edge> e;

    Graph():n(0), m(0) {}
    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
    }
    Graph(int _n, int _m) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        input(_m);
    }
    inline void add(int u, int v, int cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        g[u].emplace_back(e.size());
        //g[v].emplace_back(e.size()); // digraph remove
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;
            u--; v--; // input 1-based
            add(u, v);
        }
    }
    vector<int> pos;
    int tim;
    vector<int> low;
    vector<int> num;
    vector<int> stk;
    vector<bool> trk;
    int cnt;
    vector<int> comp;
    void scc_dfs(int u);
    void scc_run();
};

//int gloc, glocnt;

void Graph::scc_dfs(int u) {
    low[u] = num[u] = tim++;
    stk.emplace_back(u);
    trk[u] = true;
    for (; pos[u] < (int)g[u].size(); pos[u]++){
        int i = g[u][pos[u]];
        int v = e[i].u ^ e[i].v ^ u;
        if (!num[v])
            scc_dfs(v);
        if (trk[v])
            low[u] = min(low[u], low[v]);
    }
    // into scc
    if (low[u] == num[u]){
        while(true){
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            comp[k] = cnt;
            // calc this scc's nodes here
            if (k == u)
                break;
        }
        cnt++;
    }
}

void Graph::scc_run(){
    // set global val here
    stk.reserve(n);
    tim = 1;
    cnt = 0;
    comp = vector<int>(n);
    pos = vector<int>(n, 0);
    low = vector<int>(n, 0);
    num = vector<int>(n, 0);
    trk = vector<bool>(n, false);
    for (int u = 0; u < n; u++) {
        if (!num[u])
            scc_dfs(u);
    }
}

// note!: comp[i] small means in dfs first end time. i.e. rev topo. so in sat(): set less true
// process in 1.2.. order
struct TwoSat {
    int n=0;
    Graph g;
    vector<bool> res;

    // 1. create var
    int id(){
        return 2*n++;
    }
    // 2. init graph vec
    void init() {
        g.n = n<<1;
        g.g.resize(n<<1);
    }

    inline int i(int x) { return x^1; }

    // 3. add relation
    void imply(int x, int y) {
        g.add(x, y);
        g.add(i(y), i(x));
    }
    void _tr(int x) {
        g.add(i(x), x);
    }
    void _fs(int x) {
        g.add(x, i(x));
    }
    void _or(int x, int y) {
        g.add(i(x), y);
        g.add(i(y), x);
    }
    void _xor(int x, int y) {
        imply(x, i(y));
        imply(i(x), y);
    }
    void _eq(int x, int y) {
        imply(x, y);
        imply(i(x), i(y));
    }
    void _and(int x, int y) {
        _tr(x); _tr(y);
    }
    void _has_fs(int x, int y) {
        imply(x, i(y));
    }

    // 4. find sat
    bool sat() {
        g.scc_run();
        res.resize(n<<1);
        for (int k = 0; k < n; k++) {
            int x = k<<1;
            if (g.comp[x] == g.comp[i(x)]) return false;
            res[x] = g.comp[x] < g.comp[i(x)];
            res[i(x)] = res[x] ^ true;
        }
        return true;
    }
};

vector<pair<int, int>> a;

template <typename T=int>
struct Segtree {
    int n; // leaf [n, 2n), view as original [0, n)
    int sz_v;
    vector<T> v; //tree

    TwoSat ts;

    int m;
    int d;
    vector<int> nop;

    Segtree(int _d): d(_d){
        n = a.size();
        sz_v = n<<1;
        m = n >> 1;
        v.resize(sz_v);
        nop.resize(n); // nop = I
        for (int i = 0; i < m; i++) {
            nop[i<<1] = ts.id(); // same effect as iota
            nop[i<<1|1] = nop[i<<1] ^ 1;
        }
        init();
        ts.init();
        build();
        make_exclude();
//dbg(a);
//dbg(nop);
//dbg(v);
dbg(ts.g.g);
    }
    void init() {// set leaf value
        for (int i = 0; i < n; i++) {
            v[i+n] = nop[a[i].second];
            v[i] = ts.id();
        }
    }
    void build() {
        for (int i = n-1; i > 0; i--) {
            //v[i] = ts.id();
            ts.imply(v[i], v[i<<1]);
            ts.imply(v[i], v[i<<1|1]);
        }
    }
    void make_exclude() {
        for (int i = 0; i < n; i++) {
            int x = a[i].first;
            int choose = a[i].second ^ 1;
            int j = lower_bound(a.begin(), a.end(), make_pair(x+d,-1)) - a.begin();
            update(i+1, j, choose);
            j = upper_bound(a.begin(), a.end(), make_pair(x-d,1<<30)) - a.begin(); // not -1
            update(j, i, choose);
        }
    }
    bool sat() {
        return ts.sat();
    }
    //inline void update(int p, T val) {
    //    assert(p>=0);
    //    for (v[p += n] = val; p >>= 1;) {
    //        v[p] = v[p<<1] + v[p<<1|1];
    //    }
    //}

    // Note only when range-assign, single-access not interfere. e.g max
    inline void update(int l, int r, int c) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            //if (d==0) dbg(l,r,"into");
            if (l & 1) { ts.imply(c, v[l++]); }
            if (r & 1) { ts.imply(c, v[--r]); }
        }
    }
    //inline T query(int p){
    //    T res(ID);
    //    for (p += n; p > 0; p >>= 1) { res += v[p]; }
    //    return res;
    //}
};

typedef Segtree<int> Seg;

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

bool check(int d) {
    Seg s(d);
dbg(d);
    return s.sat();
}
// seg node, each repre. nop[l..r] aka, this range all not choose. aka all select dual
void solve() {
    int n; cin >> n;
    n<<=1;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
    }
    sort(a.begin(), a.end());
    const int N = 1e9+10; 
    int res = bs_last<int>(0, N, check);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
