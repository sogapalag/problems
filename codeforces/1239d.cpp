#include <bits/stdc++.h>

using namespace std;

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

// we don't use TS, use original graph
// since -> means cannot (T,F), or T implies T
// for a scc chain, it's like  F->..T->T->...->T.
// so make sure scc>=2, just set first-topo as F
void solve() {
    int n,m;
    cin >> n >> m;
    Graph g(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        if(x == y) continue;
        x--;y--;
        g.add(x,y);
    }
    if (n == 1) {
        cout << "No\n"; return;
    }

    g.scc_run();
    if (g.cnt < 2) {
        cout << "No\n"; return;
    }
    vector<int> res[2];
    for (int i = 0; i < n; i++) {
        if (g.comp[i] == g.cnt-1) {
            res[1].emplace_back(i+1);
        }else res[0].emplace_back(i+1);
    }
    cout << "Yes\n";
    cout << res[0].size() << ' ' << res[1].size() << "\n";
    for (auto& x: res[0]) {
        cout << x << ' ';
    }cout << "\n";
    for (auto& x: res[1]) {
        cout << x << ' ';
    }cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
