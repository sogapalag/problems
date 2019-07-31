#include <bits/stdc++.h>

using namespace std;

const int N = 55;

int s[N][N];
int dp[N][N][N][N];

int sum(int x, int y, int u, int v) {
    return s[u][v] - s[x-1][v] - s[u][y-1] + s[x-1][y-1];
}

int f(int x, int y, int u, int v) {
    if (sum(x,y,u,v) == 0) return 0;
    int& res = dp[x][y][u][v];
    if (res != -1) return res;
    res = max(u-x, v-y) + 1;
    // always exist split, no "风车" shape, since cost is <=max(h,w).
    for (int i = x; i < u; i++) {
        res = min(res, f(x,y,i,v) + f(i+1,y,u,v));
    }
    for (int j = y; j < v; j++) {
        res = min(res, f(x,y,u,j) + f(x,j+1,u,v));
    }
    return res;
}

void solve() {
    memset(s, 0, sizeof s);
    memset(dp, -1, sizeof dp);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char x; cin >> x;
            s[i][j] = s[i-1][j] + s[i][j-1] + (x == '#');
            dp[i][j][i][j] = (x == '#');
        }
    }
    cout << f(1,1,n,n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
