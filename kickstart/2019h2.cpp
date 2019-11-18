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
dbg(g);
dbg(n);
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
        g.g.assign(n<<1, vector<int>());
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
    int sat() {
        g.scc_run();
        res.resize(n<<1);
        int cnt = 0;
        for (int k = 0; k < n; k++) {
            int x = k<<1;
            if (g.comp[x] == g.comp[i(x)]) return false;
            res[x] = g.comp[x] < g.comp[i(x)];
            res[i(x)] = res[x] ^ true;
            if (res[x]) cnt++;
        }
        return min(cnt, n - cnt);
    }
};

void solve() {
    int n; cin >> n;
    int D = 2*n-1;
    TwoSat odd, even;
    vector<int> c(D), d(D);
    for (int i = 0; i < D; i++) {
        c[i] = ((i&1)^(n&1)) ? even.id() : odd.id();
        d[i] = (i&1)? odd.id(): even.id();
    }
dbg(c,d);
    odd.init();
    even.init();
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            int x = i-j+n-1, y = i+j;
            if (s[j] == '.') {
                if (y&1) {
                    odd._xor(c[x], d[y]);
                } else {
                    even._xor(c[x], d[y]);
                }
            } else {
                if (y&1) {
                    odd._eq(c[x], d[y]);
                } else {
                    even._eq(c[x], d[y]);
                }
            }
        }
    }
    int res = odd.sat() + even.sat();
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
