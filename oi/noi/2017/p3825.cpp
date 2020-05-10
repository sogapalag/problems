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

const int N = 5e4+10;
int id[N][3];
// the conditions tell 2sat
// note brute-force not 3^8, but 2^8, iter s='a'/'b' is enough, not car='A'/'B'/'C'
void solve() {
    int n,d;
    cin >> n >> d;
    string s; cin >> s;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        if(s[i]=='x')pos.push_back(i);
    }
    assert((int)pos.size() == d);
    TwoSat TS;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            id[i][j] = TS.id();
        }
    }
    TS.init();
    for (int i = 0; i < n; i++) {
        if (s[i]!='x') {
            TS._fs(id[i][s[i]-'a']);
            int x = 0, y = 1;
            if (x == s[i]-'a') x = 2;
            else if (y == s[i]-'a') y = 2;
            TS._xor(id[i][x], id[i][y]);
        }
    }
    int m; cin >> m;
    for (int _ = 0; _ < m; _++) {
        int i,j; char x,y;
        cin >> i >> x >> j >> y;
        --i,--j;
        TS.imply(id[i][x-'A'], id[j][y-'A']);
    }

    for (int msk = 0; msk < 1<<d; msk++) {
        auto ts = TS;
        for (int i = 0; i < d; i++) {
            int s = msk>>i&1;
            ts._fs(id[pos[i]][s]);
            int x = 0, y = 1;
            if (x==s) x = 2;
            else if (y==s) y = 2;
            ts._xor(id[pos[i]][x], id[pos[i]][y]);
        }
        if (ts.sat()) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 3; j++) {
                    if (ts.res[id[i][j]]) {
                        cout << char('A'+j);
                    }
                }
            }
            return;
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
