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
        deg = vector<int> (n,0);
    }
    vector<int> deg;
    inline void add(int u, int v, int cost=1) {
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
        int u, v, c;
        for (int i = 0; i < _m; i++) {
            cin >> u >> v;// >> c;
            u--; v--; // input 1-based
            add(u, v, 1);
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

// dij is overkill.
// simplily from u, non-direct v same group.
//
// many checks are necessary.
//
// another method, hash, since same set, their adj should be same.
void solve() {
    int n, m;
    cin >> n >> m;
    Graph g(n,m);

    vector<int> res(n,-1);
    auto d = g.dijkstra<int>(0);
    res[0] = 1;
    int group2 = -1;
    for (int i = 1; i < n; i++) {
        if (d[i] > 2) {
            cout << -1; return;
        } else if(d[i] == 2) {
            res[i] = 1;
        } else group2 = i;
    }
    
    auto d2 = g.dijkstra<int>(group2);
    res[group2] = 2;
    for (int i = 0; i < n; i++) {
        if (i==group2) continue;
        if (d2[i] > 2) {
            cout << -1; return;
        }else if (d2[i] == 2) {
            if (res[i] != -1) {
                cout << -1; return;
            }
            res[i] = 2;
        }else if (res[i] == -1) res[i] = 3;
    }


    // no inner edge
    for (auto& e: g.e) {
        if (res[e.u] == res[e.v]) {
            cout << -1; return;
        }
    }

   // // group3 need check,too. inner might edge
   // int group3 = -1;
   // for (int i = 0; i < n; i++) {
   //     if (res[i] == 3) group3 = i;
   // }
   // if (group3 == -1) {
   //     cout << -1; return;
   // }
   // auto d3 = g.dijkstra<int>(group3);
   // for (int i = 0; i < n; i++) {
   //     if (i == group3)continue;
   //     if (d3[i] > 2) {
   //         cout << -1; return;
   //     } else if(d3[i] == 2) {
   //         if (res[i] != 3) {
   //             cout << -1; return;
   //         }
   //     } else if (res[i] == 3) {
   //         cout << -1; return;
   //     }
   // }
    
    int cnt[3] = {};
    for (auto& x: res) {
        cnt[x-1]++;
    }

    // out-edge = deg
    auto check = [&](){
        for (int i = 0; i < 3; i++) {
            if (cnt[i] == 0) return false;
        }
        for (int i = 0; i < n; i++) {
            int x = res[i];
            if (n-cnt[x-1] != g.deg[i]) return false;
        }
        return true;
    };
    if (!check()) {
        cout << -1; return;
    }

    for (auto& x: res) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
