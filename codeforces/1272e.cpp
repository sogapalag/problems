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

// add odd/even dummy node, consider reverse-path
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    int even = n, odd = n+1;
    Graph g(n+2); g.set_di(true);
    for (int i = 0; i < n; i++) {
        int x; cin >> x; a[i]=x;
        if (x&1) {
            g.add(odd, i);
        } else {
            g.add(even, i);
        }
        if (i-x >= 0) {
            g.add(i-x, i);
        }
        if (i+x < n) {
            g.add(i+x, i);
        }
    }
    auto d0 = g.dijkstra(even);
dbg(d0);
    auto d1 = g.dijkstra(odd);
    for (int i = 0; i < n; i++) {
        int res = (a[i]&1) ? d0[i] : d1[i];
        if (res > (1<<25)) res = -1;
        else res--;
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
