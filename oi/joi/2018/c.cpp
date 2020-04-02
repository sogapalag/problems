#include <bits/stdc++.h>

using namespace std;

const int N = 3111; 
char s[N][N];

// the key is to note only 
//   G  could collide, (1,2) or (2,1)
//  G   1: vert, 2: hori
// this imply diag independent, so each diag simply dp. then sum it.
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> &s[i][1];
    }
    int res = 0;
    for (int k = 3; k <= n+m; k++) {
        int dp[3] = {};
        int nxt[3] = {};
        for (int i = max(1, k-m), j = k-i; i <= n && j >= 1; i++, j--) { // watch out boarder
            memset(nxt, 0, sizeof nxt);
            if (s[i][j] == 'G') {
                if (s[i-1][j] == 'R' && s[i+1][j] == 'W') {
                    nxt[1] = 1 + max(dp[0], dp[1]);
                }
                if (s[i][j-1] == 'R' && s[i][j+1] == 'W') {
                    nxt[2] = 1 + max(dp[0], dp[2]);
                }
                nxt[0] = max({dp[0], dp[1], dp[2]});
                swap(nxt, dp);
            } else {
                dp[0] = max({dp[0], dp[1], dp[2]});
                dp[1] = dp[2] = 0;
            }
        }
        res += max({dp[0], dp[1], dp[2]});
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
