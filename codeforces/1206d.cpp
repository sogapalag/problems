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
    inline void add(int u, int v, int cost=1) {
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
            u--; v--; // input 1-based
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
    const int INF = 0x3f3f3f3f;
    vector<bool> trk(n, false);
    vector<T> d(n, INF);
    d[s] = 0;
    auto comp = [&](int x, int y){
        return d[x] > d[y];
    };
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);
    pq.push(s);
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        if (trk[u])
            continue;
        trk[u] = true;
        for (int i: g[u]) {
            int v = e[i].u ^ e[i].v ^ u;
            if (d[v] > d[u] + e[i].cost) {
                d[v] = d[u] + e[i].cost;
                pq.push(v);
            }
        }
    }
    return d;
}
using ll=long long ;
template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    inline int get_id(T x) {
        if (!id.count(x)) {
            id[x] = num.size();
            num.emplace_back(x);
        }
        return id[x];
    }
    inline int get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

// for each edge remove test, cycle len = 1 + d
void solve() {
    int n; cin >> n;
    vector<vector<int>> comp(63);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        for (int j = 0; j < 63; j++) {
            if (x & (1ll<<j))
                comp[j].emplace_back(i);
        }
    }
    vector<pair<int, int>> edge;
    for (auto& c: comp) {
        if ((int)c.size() >= 3) {
            cout << 3; return;
        }
        if ((int)c.size() == 2) {
            edge.emplace_back(c[0], c[1]);
        }
    }
    dbg(edge);
    Compress<> cp;
    int tmp[200][200];
    for (auto& p: edge) {
        int i = cp.get_id(p.first);
        int j = cp.get_id(p.second);
        tmp[i][j] = tmp[j][i] = 1;
    }
    n = cp.num.size();
    if (n < 2) {
        cout << -1; return;
    }
    dbg(n);
    Graph g(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (tmp[i][j] == 1)
                g.add(i, j);
        }
    }
    int res = 1e7;
    for (auto& e: g.e) {
        int u = e.u, v = e.v;
        e.cost = 1e7;
        auto d = g.dijkstra<int>(u);
        res = min(res, 1 + d[v]);
        e.cost = 1;
    }
    if (res > n) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
