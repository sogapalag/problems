#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1024; 
const int K = 42; 
int c[N][N];
int d[K][K];
int dis[K][N][N];

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

int n,m, C;
using pi=pair<int, int> ;
// multi-source
void bfs(int color) {
    queue<pi> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (c[i][j] == color) {
                q.push({i,j});
                dis[color][i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        int i,j;
        tie(i,j) = q.front(); q.pop();
        for (int _ = 0; _ < 4; _++) {
            int x = i+dx[_];
            int y = j+dy[_];
            if (0<=x&&x<n && 0<=y&&y<m) {
                if (dis[color][x][y]==INF) {
                    dis[color][x][y] = dis[color][i][j] + 1;
                    q.push({x,y});
                    int k = c[x][y];
                    d[color][k] = d[k][color] = min(d[k][color], dis[color][x][y] + 1); // +1, since into k
                }
            }
        }
    }
}
// (,)->(first) color x ->(many alter-color)(floyd-warshall)-> color y (last)->(,)
void solve() {
    memset(d, INF, sizeof d);
    memset(dis, INF, sizeof dis);
    cin >> n >> m >> C;
    for (int i = 0; i < C; i++) {
        d[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x; x--;
            c[i][j] = x;
        }
    }
    for (int i = 0; i < C; i++) {
        bfs(i);
    }

    for (int k = 0; k < C; k++) {
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                if (d[i][k] < INF && d[k][j] < INF) {// for negative
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int i,j, x,y;
        cin >> i >> j >> x >> y;
        i--;j--;x--;y--;
        int res = abs(x-i) + abs(y-j);
        for (int k0 = 0; k0 < C; k0++) {
            for (int k1 = 0; k1 < C; k1++) {
                res = min(res, dis[k0][i][j] + dis[k1][x][y] + d[k0][k1] + 1); // +1 since first into k0
            }
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
