#include <bits/stdc++.h>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n+2, string(m+2, '#'));
    for (int i = 1; i <= n; i++) {
        cin >> &(s[i][1]);
    }
    vector<vector<int>> d(n+2, vector<int>(m+2, -1));
    queue<pair<int, int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '1') {
                d[i][j] = 0;
                q.push(make_pair(i, j));
            }
        }
    }
    while (!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        for (int k = 0; k < 4; k++) {
            int ii = i + dx[k];
            int jj = j + dy[k];
            if (s[ii][jj] == '0' && d[ii][jj] == -1) {
                d[ii][jj] = d[i][j] + 1;
                q.push(make_pair(ii, jj));
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << d[i][j] << ' ';
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
    cout << endl;
}
