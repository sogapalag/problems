#include <bits/stdc++.h>

using namespace std;
using ll=long long;

    struct Edge {
        int u, v;
        ll cost;
        Edge(int _u, int _v, ll _cost) : u(_u), v(_v), cost(_cost) {}
        bool operator<(const Edge& _e) const{
            return cost < _e.cost;
        }
    };
struct Graph {
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
    inline void add(int u, int v, ll cost=1) {
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
        int u, v, c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v >> c;
            //u--; v--; // input 1-based
            add(u, v, c);
        }
    }
    template <typename T=int>
    vector<T> dijkstra(int s);
};

// single source shortest path
template <typename T>
vector<T> Graph::dijkstra(int s) {
    // modify T's INF
    //const int INF = 0x3f3f3f3f;
    const long long INF = 0x3f3f3f3f3f3f3f3f;
    vector<bool> trk(n, false);
    vector<T> d(n, INF);
    d[s] = 0;
    using pi=pair<T,int>;
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        T dis; int u;
        tie(dis, u) = pq.top();
        pq.pop();
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
const int N = 3e5+10; 
ll res[N];

struct Dsu {
    int n;
    vector<int> p;
    vector<set<int>> r; // hint
    
    Dsu(int _n) { n = _n; p.resize(n); r.resize(n); init(); }
    inline void init() {
        for (int i = 0; i < n; i++) {
            p[i] = i;
        }
    }
    inline int find(int x) {
        return p[x] == x ? x: p[x] = find(p[x]);
    }
    inline bool join(const Edge& e) {
        int x = find(e.u), y = find(e.v);
        if (x == y) return false;
        if (r[x].size() < r[y].size()) swap(x,y);
        p[y] = x;
        for (auto& i: r[y]) {
            auto it = r[x].find(i);
            if (it != r[x].end()) {
                r[x].erase(it);
                res[i] = e.cost;
            } else {
                r[x].insert(i);
            }
        }
        return true;
    }
    //inline bool join(int x, int y) {
    //    x = find(x); y = find(y);
    //    if (x == y) return false;
    //    if (r[x] < r[y]) swap(x, y);
    //    p[y] = x; r[x] += r[y];
    //    return true;
    //}
    inline bool check(int x, int y) {
        return find(x) == find(y);
    }
};

// offline
void solve() {
    int n,m,k,q;
    cin >> n >> m >> k >> q;
    int C = 0; // dummy center, for multi-source
    Graph g(n+1);
    for (int i = 1; i <= k; i++) {
        g.add(C, i, 0);
    }
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        g.add(x,y,z);
    }
    auto dis = g.dijkstra<ll>(C);
    // replace weight
    vector<Edge> es; es.reserve(m);
    for (int i = 0; i < m; i++) {
        auto& e = g.e[i+k];
        es.emplace_back(e.u, e.v, e.cost + dis[e.u] + dis[e.v]);
    }
    sort(es.begin(), es.end());
    Dsu d(n+1);
    for (int i = 0; i < q; i++) {
        int x,y;
        cin >> x >> y;
        d.r[x].insert(i);
        d.r[y].insert(i);
    }
    
    for (auto& e: es) {
        d.join(e);
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
