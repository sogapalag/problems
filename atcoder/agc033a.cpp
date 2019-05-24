#include <bits/stdc++.h>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// multi-source bfs, maximum dist.
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n+2, string(m+2, '*'));
    vector<vector<int>> d(n+2, vector<int>(m+2, -1)) ;
    for (int i = 1; i <= n; i++) {
        cin >> &s[i][1];
    }
    queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#') {
                q.emplace(i, j);
                d[i][j] = 0;
            }
        }
    }
    int res = 0;
    while (!q.empty()) {
        pair<int, int> p = q.front();
        int x = p.first;
        int y = p.second; 
        q.pop();
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (s[xx][yy] == '.' && d[xx][yy] == -1) {
                d[xx][yy] = d[x][y] + 1;
                res = max(res, d[xx][yy]);
                q.emplace(xx, yy);
            }
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
