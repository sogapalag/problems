#include <bits/stdc++.h>

using namespace std;


void solve(){

// SNIPPETS_START graph_mat_dijkstra
const int INF = 0x3f3f3f3f;
const int N = 3000; 

int cost[N][N];
// move above global

memset(cost, INF, sizeof cost);

int n, m;
cin >> n >> m;
for (int i = 0; i < n; i++) {
    cost[i][i] = 0;
}
struct Edge {
    int u, v;
    int c;
};
vector<Edge> e(m);
for (int i = 0; i < m; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    x--; y--; // 1-based
    cost[x][y] = cost[y][x] = min(cost[x][y], z);
    e[i] = {x, y, z};
}

auto dijkstra = [&](int s){
    vector<int> d(n, INF);
    vector<bool> trk(n, false);
    d[s] = 0;
    while (true) {
        int mindis = INF;
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
};

auto d = dijkstra(0);
// SNIPPETS_END

}
