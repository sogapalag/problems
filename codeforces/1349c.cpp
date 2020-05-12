#include <bits/stdc++.h>

using namespace std;
using pi=pair<int, int> ;
using ll=long long;

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
// compo will flip repeatedly.
// isolated stay untill it is affected by some compo
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> s(n);
    for (auto& x: s) cin >> x;
    vector<vector<int>> d(n, vector<int>(m,-1));
#define in(i,j) (0<=i&&i<n && 0<=j&&j<m)
    queue<pi> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int _ = 0; _ < 4; _++) {
                int x = i+dx[_];
                int y = j+dy[_];
                if (in(x,y) && s[i][j]==s[x][y]) {
                    d[i][j] = 0;
                    q.emplace(i,j); break;
                }
            }
        }
    }
    // all iso.
    if (q.empty()) {
        while (k--) {
            int i,j; ll t;
            cin >> i >> j >> t; --i;--j;
            cout << s[i][j] << '\n';
        }
        return;
    }
    // bfs
    while (!q.empty()) {
        int i,j;
        tie(i,j) = q.front(); q.pop();
        for (int _ = 0; _ < 4; _++) {
            int x = i + dx[_];
            int y = j + dy[_];
            if (in(x,y) && d[x][y] == -1) {
                d[x][y] = d[i][j] + 1;
                q.emplace(x, y);
            }
        }
    }
    while (k--) {
        int i,j; ll t;
        cin >> i >> j >> t; --i;--j;
        if (t <= d[i][j]) {
            cout << s[i][j] << '\n';
        } else {
            t -= d[i][j];
            char x = s[i][j];
            if (t&1) x = x=='0'?'1':'0';
            cout << x << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
