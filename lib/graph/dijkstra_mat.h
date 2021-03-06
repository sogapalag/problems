#include <bits/stdc++.h>

using namespace std;

// SNIPPETS_START graph_mat_dijkstra
struct Graph {
    int n;
    using CT = int; static const CT INF = 0x3f3f3f3f;
    //using CT = long long; static const CT INF = 0x3f3f3f3f3f3f3f3f;
    vector<vector<CT>> cost;
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
        input();
    }
    void input() {
        if (is_digraph) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cin >> cost[i][j];
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    CT x; cin >> x;
                    cost[i][j] = cost[j][i] = min(cost[i][j], x);
                }
            }
        }
    }

    vector<CT> dijkstra(int s){
        vector<CT> d(n, INF);
        vector<bool> trk(n, false);
        d[s] = 0;
        while (true) {
            CT mindis = INF;
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (!trk[i] && d[i] < mindis) {
                    u = i; mindis = d[i];
                }
            }
            if (u == -1) break;
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
// SNIPPETS_END
