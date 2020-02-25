#include <bits/stdc++.h>

using namespace std;

const int L = 17; 
const int N = 1<<L; 
int dp[L+1][N][2][2];
// [i, i+2^j) create w(x), l(y) whether fan of. above space can optim, omit.

// double-elimination, the hard part is understand the tree structure.
// it's indeed a pbbt, every valid 2^j, create 1w, 1l 
//  merge process: two 2^j, 2^j, has another 3 matchs, ww, ll, lofw vs wofl
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> fan(1<<n);
    for (int _ = 0; _ < k; _++) {
        int x; cin >> x; x--;
        fan[x] = 1;
    }
    memset(dp, 0xc0, sizeof dp);
    for (int i = 0; i < 1<<n; i+=2) {
        int x = fan[i] + fan[i^1];
        if (x == 0) {
            dp[1][i][0][0] = 0;
        } else if (x == 1) {
            dp[1][i][1][0] = dp[1][i][0][1] = 1;
        } else if (x == 2) {
            dp[1][i][1][1] = 1;
        }
    }
    auto maxi = [](int& x, int y){
        if (x < y) x = y;
    };
#define rep(x) for (int x:{0,1})
    for (int j = 2; j <= n; j++) {
        for (int i = 0; i < 1<<n; i+=(1<<j)) {
            rep(x)rep(y)rep(u)rep(v){
                int base = dp[j-1][i][x][y] + dp[j-1][i+(1<<(j-1))][u][v];
                // 2^3 result, but no need ugly-loop, since among ll and lofw, it's optim to keep a fan join if there's.
                // ww , ll
                base += (x||u) + (y||v);
                // lofw vs wofl
                maxi(dp[j][i][x][u || (y||v)], base + (u||(y||v)));
                maxi(dp[j][i][u][x || (y||v)], base + (x||(y||v)));
            }
        }
    }
    int res = 0;
    rep(x)rep(y){
        maxi(res, dp[n][0][x][y] + (x||y));
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
