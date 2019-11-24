#include <bits/stdc++.h>

using namespace std;

struct Graph {
    using CT = int; static const CT INF = 0x3f3f3f3f;
    //using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
    struct Edge {
        int u, v;
        CT cost;
        Edge(int _u, int _v, CT _cost) : u(_u), v(_v), cost(_cost) {}
    };
    int n, m;
    bool is_digraph;
    vector<vector<int>> g;
    vector<Edge> e;

    Graph(int _n) : n(_n), m(0) {
        assert(n >= 1);
        g.resize(n);
        set_di(false);
    }
    Graph(int _n, int _m, bool _di=false) : n(_n), m(0), deg(n,0), co(n), trk(n,false) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        pos = vector<int>(n, 0);
        is_digraph = _di;
    }
    vector<int> deg;
    inline void add(int u, int v, CT cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    void input(int _m) {
        int u, v;// CT c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;// >> c;
            u--; v--; // input 1-based
            add(u, v);//, c);
        }
    }
    vector<int> pos;
    vector<int> co;
    vector<bool> trk;
    int k;
    void dfs(int u, int x) {
        trk[u] = true;
        for (; pos[u] < (int)g[u].size(); pos[u]++) {
            int i = g[u][pos[u]];
            int v = e[i].u ^ e[i].v ^ u;
            // rule
            if (!trk[v]) {
                (x+=1)%=k;
                co[i] = x;
                dfs(v, x);
            }
        }
    }
    
    void run() {
        int rt = max_element(deg.begin(), deg.end()) - deg.begin();
        k = deg[rt];
        dfs(rt, 0);
        cout << k << "\n";
        for (int i = 0; i < n-1; i++) {
            cout << co[i]+1 << "\n";
        }
    }
};

void solve() {
    int n; cin >> n;
    Graph g(n, n-1);
    g.run();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
