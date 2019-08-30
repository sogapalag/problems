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
    string res;
    char cnt;
    void scc_dfs(int u);
    void scc_run();
};

//int gloc, glocnt;

void Graph::scc_dfs(int u) {
    low[u] = num[u] = tim++;
    stk.emplace_back(u);
    trk[u] = true;
    for (; pos[u] < g[u].size(); pos[u]++){
        int i = g[u][pos[u]];
        int v = e[i].u ^ e[i].v ^ u;
        if (!num[v])
            scc_dfs(v);
        if (trk[v])
            low[u] = min(low[u], low[v]);
    }
    // into scc
    if (low[u] == num[u]){
        // init scc sub_glob here
        while(true){
            int k = stk.back();
            stk.pop_back(); trk[k] = false;
            // calc this scc's nodes here
            if (cnt < 'a') cnt ='a';
            res[k] = cnt;
            if (k == u)
                break;
        }
        cnt--;
        // calc scc sub_glob here
    }
}

void Graph::scc_run(){
    res.resize(n);
    cnt = 'z';
    // set global val here
    stk.reserve(n);
    tim = 1;
    pos = vector<int>(n, 0);
    low = vector<int>(n, 0);
    num = vector<int>(n, 0);
    trk = vector<bool>(n, false);
    for (int u = 0; u < n; u++) {
        if (!num[u])
            scc_dfs(u);
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    Graph g(n);
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    for (int i = 1; i < n; i++) {
        g.add(a[i-1], a[i]);
    }
    for (auto& x: a) {
        cin >> x;
        x--;
    }
    for (int i = 1; i < n; i++) {
        g.add(a[i-1], a[i]);
    }
    g.scc_run();
    if ('z'-g.cnt < k) {
        cout << "NO";
    } else {
        cout << "YES\n";
        cout << g.res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
