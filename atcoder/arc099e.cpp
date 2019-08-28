#include <bits/stdc++.h>

using namespace std;

const int N = 711;
bool g[N][N];
bool col[N], trk[N];
int sz[N][2];
bool dp[N][2*N];

void solve() {
    int n,m;
    cin >> n >> m;
    memset(g, 1, sizeof g);
    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
    }
    for (int _ = 0; _ < m; _++) {
        int x, y;
        cin >> x >> y;
        g[x][y] = g[y][x] = 0;
    }
    // bfs
    int cnt = 0;
    memset(trk, 0, sizeof trk);
    memset(sz, 0, sizeof sz);
    for (int i = 1; i <= n; i++) {
        if (trk[i]) continue;
        cnt++;
        col[i] = 0; trk[i] = 1;
        sz[cnt][0]++;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 1; v <= n; v++) {
                if (!g[u][v])continue;
                if (trk[v]) {
                    if (col[u]==col[v]) {
                        cout << -1; return;
                    }
                } else {
                    col[v] = col[u] ^ 1; trk[v] = 1;
                    sz[cnt][col[v]]++;
                    q.push(v);
                }
            }
        }
    }
    // dp
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int i = 1; i <= cnt; i++) {
        int x = sz[i][0], y = sz[i][1];
        for (int j = 0; j <= n; j++) {
            dp[i][j + x] |= dp[i-1][j];
            dp[i][j + y] |= dp[i-1][j];
        }
    }
    int res = 1e8;
    for (int i = 0; i <= n; i++) {
        if (dp[cnt][i]) {
            res = min(res, i*(i-1)/2 + (n-i)*(n-i-1)/2);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
