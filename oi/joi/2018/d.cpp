#include <bits/stdc++.h>

using namespace std;

struct Graph {
    //using CT = int; static const CT INF = 0x3f3f3f3f;
    using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
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
    Graph(int _n, int _m, bool _di=false) : n(_n) {
        assert(n >= 1);
        g.resize(n);
        e.reserve(_m);
        m = 0;
        set_di(_di);
        input(_m);
    }
    void set_di(bool _di) {
        is_digraph = _di;
    }
    inline void add(int u, int v, CT cost=1) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (is_digraph) {
            //outdeg[u]++; indeg[v]++;
            g[u].emplace_back(m);

        } else {
            //deg[u]++; deg[v]++;
            g[u].emplace_back(m);
            g[v].emplace_back(m);
        }
        e.emplace_back(u, v, cost);
        m++;
    }
    int S, T, U , V;
    void input(int _m) {
        cin >> S >> T >> U >> V;
        S--;T--;U--;V--;
        int u, v; CT c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c;
            u--; v--; // input 1-based
            add(u, v, c);
        }
    }

    // if multi-source, add dummy SOURCE
    // single source shortest path
    vector<CT> dijkstra(int s) {
        vector<bool> trk(n, false);
        vector<CT> d(n, INF);
        d[s] = 0;
        using pi=pair<CT,int>;
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, s});
        while (!pq.empty()) {
            CT dis; int u;
            tie(dis, u) = pq.top(); pq.pop();
            if (trk[u])
                continue;
            trk[u] = true;
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (d[v] > d[u] + e[i].cost) {
                    d[v] = d[u] + e[i].cost;
                    pq.push({d[v], v});
                }
            }
        }
        return d;
    }

    // first note U -> V can use contionous free-edges.
    // let dpu[x] := U -> x through a continous free-edges
    // U -> V => U-> x ->V := dpu[x] + dv[x]
    void solve() {
        auto ds = dijkstra(S);
        auto du = dijkstra(U);
        auto dv = dijkstra(V);
        auto res = du[V];
        auto dpu = du;
        auto dpv = dv;
        vector<bool> trk(n);
        // dfs the free edges, view as DAG
        function<void(int)> dfs = [&](int u){
            trk[u] = true;
            for (int i:g[u]) {
                int v = e[i].u^e[i].v^u;
                //if (trk[v]) continue;
                if (ds[u] != ds[v] + e[i].cost) continue;
                if (!trk[v]) dfs(v);
                dpu[u] = min(dpu[u], dpu[v]);
                dpv[u] = min(dpv[u], dpv[v]);
            }
            res = min(res, dpu[u] + dv[u]);
            res = min(res, dpv[u] + du[u]);
        };
        if (du[S] < INF)dfs(T);
        cout << res << "\n";
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Graph g(n,m);
    g.solve();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
