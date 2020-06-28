#include <bits/stdc++.h>

using namespace std;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

// another(editorial): dijkstra cost 1/k, when change direction round-up
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    int sx,sy,tx,ty;
    cin >> sx >> sy >> tx >> ty;
    --sx;--sy;--tx;--ty;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    vector<vector<int>> d(n, vector<int>(m, -1));
    d[sx][sy] = 0;
    queue<pair<int,int>> q;
    q.emplace(sx, sy);
    while (!q.empty()) {
        int x,y;
        tie(x,y) = q.front(); q.pop();
        for (int _ = 0; _ < 4; _++) {
            for (int i = 1; i <= k; i++) {
                int u = x + i*dx[_];
                int v = y + i*dy[_];
                if (u<0||u>=n || v<0||v>=m) break;
                if (s[u][v] == '@') break;
                // each u,v can only be 4 nearest d-1 trigger. so complxity hold
                if (d[u][v] != -1 && d[u][v] < d[x][y]+1) break;
                if (d[u][v] == -1) {
                    d[u][v] = d[x][y] + 1;
                    q.emplace(u, v);
                }
            }
        }
    }
    cout << d[tx][ty];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
