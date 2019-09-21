#include <bits/stdc++.h>

using namespace std;

    const int INF = 0x3f3f3f3f;
    const int N = 300; 

int d[N][N];

int cost[8][8];
int dp[1<<8][8];

void solve() {
    int n,m, R;
    cin >> n >> m >> R;
    vector<int> a(R);
    for (int i = 0; i < R; i++) {
        cin >> a[i]; a[i]--;
    }
    memset(d, INF, sizeof d);
    for (int _ = 0; _ < m; _++) {
        int x,y,z;
        cin >> x >> y >> z;
        x--;y--;
        d[x][y] = d[y][x] = min(d[x][y], z);
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

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < R; j++) {
            cost[i][j] = d[a[i]][a[j]];
        }
    }

    const int MSK = 1<<R; 
    memset(dp, INF, sizeof dp);
    dp[0][0] = 0;
    for (int msk = 0; msk < MSK; msk++) {
        for (int i = 0; i < R; i++) {
            if (msk & (1<<i)) continue;
            for (int j = 0; j < R; j++) {
                if (msk & (1<<j)) {
                    dp[msk ^ (1<<i)][i] = min(dp[msk^(1<<i)][i], dp[msk][j] + cost[j][i]);
                }
            }
            if (msk == 0) dp[1<<i][i] = 0;
        }
    }
    int res = INF;
    for (int i = 0; i < R; i++) {
        res = min(res, dp[MSK-1][i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
