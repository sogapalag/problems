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
        e.reserve(3e6+50);
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
    void input(int _m) {
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
};
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
// O(knm log (nm)) , TLE. cause log, but idea much simpler
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    int N = n*m + k;
    Graph g(N); g.set_di(false);
    auto f = [&](int i, int j){
        return i*m + j;
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; x--;
            g.add(f(i,j), n*m + x, 1);
            for (int _: {0,2}){
                int x = i+dx[_];
                int y = j+dy[_];
                if (0<=x&&x<n && 0<=y&&y<m) {
                    g.add(f(i,j), f(x,y), 2);
                }
            }
        }
    }
    vector<vector<int>> dis(k);
    for (int x = 0; x < k; x++) {
        dis[x] = move(g.dijkstra(n*m+x));
    }

    int q; cin >> q;
    while (q--) {
        int i,j, x,y;
        cin >> i >> j >> x >> y;
        i--;j--;x--;y--;
        int res = abs(x-i) + abs(y-j);
        // meet at some color
        for (int _ = 0; _ < k; _++) {
            int ans = dis[_][f(i,j)] + dis[_][f(x,y)];
            res = min(res, ans/2);
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
