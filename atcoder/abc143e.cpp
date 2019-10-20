#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 300; 

ll d[N][N];
ll a[N][N];
// mark <= L dist=1
// do f-w again.
void solve() {
    int n,m, L;
    cin >> n >> m >> L;
    memset(d, 0x3f, sizeof d);
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        if (z > L) continue;
        d[x][y] = d[y][x] = z;
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
    
    memset(a, 0x3f, sizeof a);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] <= L) a[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        a[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][k] < INF && a[k][j] < INF) {// for negative
                    a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
                }
            }
        }
    }


    int q; cin >> q;
    while (q--) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        int res = a[x][y] == INF? -1: a[x][y]-1;
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
