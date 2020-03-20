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
        set_di(true);
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
    // work when cost only 0 or c
    vector<CT> _01bfs(int s, int t) {
        vector<CT> d(n, INF);
        d[s] = 0;
        deque<int> q;
        q.push_front(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int i: g[u]) {
                int v = e[i].u ^ e[i].v ^ u;
                if (d[v] > d[u] + e[i].cost) {
                    d[v] = d[u] + e[i].cost;
                    if (v == t) {
                        cout << d[v]; exit(0);
                    }
                    if (e[i].cost)
                        q.push_back(v);
                    else
                        q.push_front(v);
                }
            }
        }
        return d;
    }

    int create() {
        g.emplace_back();
        return n++;
    }
};

// TLE #6 #10, MLE #13
void solve() {
    int n,m;
    cin >> n >> m;
    const int B = min((int)sqrt(n), 100); 
    Graph g(n*(B+2));
    auto id = [&](int i, int d){
        return d*n + i;
    };
    for (int d = 1; d < B; d++) {
        for (int i = 0; i+d < n; i++) {
            g.add(id(i, d), id(i+d, d), 1);
            g.add(id(i+d, d), id(i, d), 1);
        }
        for (int i = 0; i < n; i++) {
            g.add(id(i, d), i, 0);
        }
    }
    int s, t;
    for (int _ = 0; _ < m; _++) {
        int i,d;
        cin >> i >> d;
        if (_==0)s=i;
        if (_==1)t=i;
        if (d < B) {
            g.add(i, id(i, d), 0);
        } else {
            for (int l = i-d, crt = i; l >= 0; l-=d) {
                int nxt = g.create();
                g.add(crt, nxt, 1);
                g.add(nxt, l, 0);
                crt = nxt;
                //g.add(i, l, (i-l)/d);
            }
            for (int r = i+d, crt = i; r < n; r+=d) {
                int nxt = g.create();
                g.add(crt, nxt, 1);
                g.add(nxt, r, 0);
                crt = nxt;
                //g.add(i, r, (r-i)/d);
            }
        }
    }
    //cout << g.dijkstra(s)[t]; //-1
    //auto res = g._01bfs(s)[t];
    //if (res == g.INF) res = -1;
    //cout << res;
    if (s==t) {
        cout << 0; return;
    }
    g._01bfs(s,t); cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
