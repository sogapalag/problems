#include <bits/stdc++.h>

using namespace std;

int cost[33][33];
int cnt[3][33];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> cost[i][j];
        }
    }
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; cin >> x;
            cnt[(i+j)%3][x]++;
        }
    }
    int res = 1e9;
#define rep(x) for(int x=1;x<=m;x++)
    rep(x)rep(y)rep(z){
        if (x==y || x==z || y==z) continue;
        int sum = 0;
        rep(i) sum += cnt[0][i] * cost[i][x];
        rep(i) sum += cnt[1][i] * cost[i][y];
        rep(i) sum += cnt[2][i] * cost[i][z];
        res = min(res, sum);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
