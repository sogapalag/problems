#include <bits/stdc++.h>

using namespace std;
using ld=long double;

struct Graph {
    int n;
    const ld INF = 1e50;
    vector<vector<ld>> cost;
    bool is_digraph;

    Graph(int _n, bool _di=false) : n(_n) {
        cost.resize(n);
        for (int i = 0; i < n; i++) {
            cost[i].assign(n, INF);
        }
        for (int i = 0; i < n; i++) {
            cost[i][i] = 0;
        }
        is_digraph = _di;
        //input();
    }
    template <typename T>
    vector<T> dijkstra(int s){
        //const T INF = 0x3f3f3f3f3f3f3f3f; 
        vector<T> d(n, INF);
        vector<bool> trk(n, false);
        d[s] = 0;
        while (true) {
            T mindis = INF;
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!trk[i] && d[i] < mindis) {
                    u = i; mindis = d[i];
                }
            }
            if (!~u) break;
            trk[u] = true;
            for (int v = 0; v < n; v++) {
                if (!trk[v] && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                }
            }
        }
        return d;
    }
};

struct Barrier {
    int x, y, r;
    Barrier() {}
    Barrier(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
    ld dist(const Barrier _b) {
        ld dx = x - _b.x;
        ld dy = y - _b.y;
        return max((ld)0.0, sqrt(dx*dx+dy*dy) - r - _b.r);
    }
};

void solve() {
    vector<Barrier> a;
    int x,y;
    cin >> x >> y;
    a.emplace_back(x,y,0);
    cin >> x >> y;
    a.emplace_back(x,y,0);
    
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x,y,r;
        cin >> x >> y >> r;
        a.emplace_back(x,y,r);
    }
    Graph g(n+2);
    for (int i = 0; i <= n+1; i++) {
        for (int j = i+1; j <= n+1; j++) {
            g.cost[i][j] = g.cost[j][i] = a[i].dist(a[j]);
        }
    }
    auto d = g.dijkstra<ld>(0);
    ld res = d[1];
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
