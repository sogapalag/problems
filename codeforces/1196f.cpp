#include <bits/stdc++.h>

using namespace std;

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
    //const int INF = 0x3f3f3f3f;
    const long long INF = 0x3f3f3f3f3f3f3f3f;
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

template <typename T=int>
struct Compress {
    map<T, int> id;
    vector<T> num;

    Compress(vector<T> v) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        num = v;
        for (int i = 0; i < (int)num.size(); i++) {
            id[num[i]] = i;
        }
    }

    inline int get_id(T x) {
        assert(id.count(x));
        return id[x];
    }
    inline T get_num(int i) {
        assert(0 <= i && i < num.size());
        return num[i];
    }
};

struct Edge {
    int u, v;
    int cost;
    Edge() {}
};

// m = min(k, m)
// only these edges might result new graph
// then brute-force
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Edge> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].cost;
    }
    sort(e.begin(), e.end(), [&](auto& u, auto& v){
            return u.cost < v.cost;
            });
    m = min(k, m);
    vector<int> new_nodes;
    for (int i = 0; i < m; i++) {
        new_nodes.emplace_back(e[i].u);
        new_nodes.emplace_back(e[i].v);
    }
    Compress<int> comp(new_nodes);
    n = comp.num.size();
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u = comp.get_id(e[i].u);
        int v = comp.get_id(e[i].v);
        g.add(u, v, e[i].cost);
    }

    vector<long long> res;
    for (int i = 0; i < n; i++) {
        auto d = g.dijkstra<long long>(i);
        for (int j = i+1; j < n; j++) {
            res.emplace_back(d[j]);
        }
    }
    sort(res.begin(), res.end());
    cout << res[k-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
