#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 300; 
int d[N][N];

// V1 V3 V5 ..
// V2 V4 ...
// form bip
void solve() {
    int n; cin >> n;
    memset(d, INF, sizeof d);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') d[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }
    // check bip
    vector<int> co(n, -1);
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (co[u] == -1) co[u] = 0;
        for (int v = 0; v < n; v++) {
            if (d[u][v] == 1) {
                if (co[v] == -1) {
                    co[v] = co[u] ^ 1;
                    q.push(v);
                } else if ((co[v]^co[u]) == 0) {
                    cout << -1; return;
                }
            }
        }
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
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res = max(res, d[i][j]);
        }
    }
    cout << res+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
