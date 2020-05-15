#include <bits/stdc++.h>

using namespace std;

const int N = 512; 
const int B = 32; 
int dp[N][N];
// greedy fail. counter-case? but there's a case show order matter:
//   (2,2) (1,3) (3,1) when remain x=4,y=4. take (2,2) is bad.
// one can get easy dp O(n^4).
// key: i,j<=B. thus O(n^3), editorial has better bound. omit.
void solve() {
    int n,m;
    cin >> n >> m;
    memset(dp, 0, sizeof dp);
    for (int k = 1; k <= B+B; k++) {
        for (int i = 0, j = k; i <= B && i <= k; i++, j--) {
            for (int x = n-i; x >= 0; x--) {
                for (int y = m-j; y >= 0; y--) {
                    dp[x+i][y+j] = max(dp[x+i][y+j], dp[x][y] + 1);
                }
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            res = max(res, dp[i][j]);
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
