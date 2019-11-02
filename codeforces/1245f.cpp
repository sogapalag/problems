#include <bits/stdc++.h>

using namespace std;
using ll=long long;
#define rep(i) for(int i=0;i<2;i++)
const int L = 31;
ll dp[L+1][2][2][2];
// [i][x][y][z], x,y,z means l < a < b < r hold? i.e. 0 means prefix still equal

// editorial method, use property when consider l,r right-most. f(l<<1, r<<1) = 3 * f(l,r) 
void solve() {
    int l,r;
    cin >> l >> r;
    ll res = 0;
    if (l == 0) {
        res += 2*r + 1;
        l = 1;
    }
    if (r <= 1) {
        cout << res << "\n"; return;
    }
    if (__builtin_clz(l) == __builtin_clz(r)) {
        cout << res << '\n'; return;
    }
    memset(dp, 0, sizeof dp);
    dp[L][0][0][0] = 1;
    for (int i = L-1; i >= 0; i--) {
        int bl = (l>>i)&1;
        int br = (r>>i)&1;
        rep(x)rep(y)rep(z)rep(u)rep(v) {
            if (u && v) continue;
            if (!x && bl && !u) continue;
            if (!y && u && !v) continue;
            if (!z && !br && v) continue;
            int nx = x || (u > bl);
            int ny = y || (v > u);
            int nz = z || (br > v);
            dp[i][nx][ny][nz] += dp[i+1][x][y][z];
        }
    }
    ll tmp = 0;
    rep(x)rep(y)rep(z) tmp += dp[0][x][y][z];
    res += tmp<<1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
