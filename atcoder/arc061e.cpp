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
    vector<T> _01bfs(int s);
};

// work when cost only 0 or c
template <typename T>
vector<T> Graph::_01bfs(int s) {
    const int INF = 0x3f3f3f3f;
    vector<T> d(n, INF);
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
                if (e[i].cost)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
    return d;
}
map<int, int> id[100005];
int nd_cnt = 0;
int get_id(int x, int c) {
    if (id[x].count(c)) return id[x][c];
    else return id[x][c]=nd_cnt++;
}
// whenever switch color, xc -> y0 -> zc' (1+1) cost
void solve() {
    int n,m;
    cin >> n >> m;
    Graph g(n+2*m);
    for (int i = 0; i < n; i++) {
        get_id(i, 0);
    }
    for (int _ = 0; _ < m; _++) {
        int x,y,c;
        cin >> x >> y >> c;
        x--;y--;
        int x0 = get_id(x,0);
        int y0 = get_id(y,0);
        int xc = get_id(x,c);
        int yc = get_id(y,c);
        g.add(xc, yc, 0);
        g.add(x0, yc, 1);
        g.add(xc, y0, 1);
    }
    int res = g._01bfs<>(0)[n-1];
    if (res > 3000000) res = -1;
    else res >>= 1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
