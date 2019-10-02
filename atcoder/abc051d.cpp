#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

const int N = 120; 

int d[N][N];

struct Edge {
    int x, y, c;
    Edge() {}
    Edge(int _x, int _y, int _c) : x(_x), y(_y), c(_c) {}
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<Edge> es(m);
    memset(d, INF, sizeof d);
    for (int i = 0; i < m; i++) {
        int x,y,c;
        cin >> x >> y >> c;
        x--;y--;
        es.emplace_back(x,y,c);
        d[x][y] = d[y][x] = c;
    }
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {// for negative
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }
    int cnt = 0;
    for (auto& e: es) {
        if (d[e.x][e.y] < e.c) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
