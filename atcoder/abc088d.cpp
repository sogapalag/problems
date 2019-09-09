#include <bits/stdc++.h>

using namespace std;

char s[55][55];
int d[55][55];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
void solve() {
    int n,m;
    cin >> n >> m;
    memset(s, '#', sizeof s);
    for (int i = 1; i <= n; i++) {
        cin >> (s[i]+1);
    }
    memset(d, 0x3f, sizeof d);
    d[1][1] = 1;
    queue<pair<int, int>> q;
    q.emplace(1,1);
    while (!q.empty()) {
        int x,y;
        tie(x,y) = q.front(); q.pop();
        for (int k = 0; k < 4; k++) {
            int u = x+dx[k], v = y+dy[k];
            if (s[u][v] == '.' && d[u][v]>1e5) {
                d[u][v] = 1 + d[x][y];
                q.emplace(u,v);
            }
        }
    }
    if (d[n][m] > 1e5) {
        cout << -1; return;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#') cnt++;
        }
    }
    int res = n*m - cnt - d[n][m];
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
