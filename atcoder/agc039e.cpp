#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 42; 
bool g[N][N];
ll dp[N][N][N][N][2];

// key part is understand the tree is form +++++++
// for up/down side of +, is recursive form +++
// check editorial dp def. https://img.atcoder.jp/agc039/editorial.pdf
void solve() {
    int n; cin >> n;
    n <<= 1;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = 1; j <= n; j++) {
            g[i][j] = s[j-1] == '1';
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n+1; j++) {
            dp[i][i-1][j][j-1][0] = dp[i][i-1][j][j-1][1] = 1;
        }
    }

    for (int a = n; a >= 2; a--) {
        for (int b = a; b < n; b++) {
            for (int c = n; c > b; c--) {
                for (int d = c; d <= n; d++) {
                    for (int p = a; p <= b; p++) {
                        for (int q = c; q <= d; q++) {
                            if (g[p][q]) {
                                dp[a][b][c][d][0] += dp[a][p-1][p+1][b][1] * dp[c][q-1][q+1][d][1];
                            }
                        }
                    }
                    for (int p = a; p <= b; p++) {
                        for (int q = c; q <= d; q++) {
                            dp[a][b][c][d][1] += dp[a][p][q][d][0] * dp[p+1][b][c][q-1][1];
                        }
                    }
                }
            }
        }
    }

    ll res = 0;
    for (int a = 2; a <= n; a++) {
        if (g[1][a]) res += dp[2][a-1][a+1][n][1];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
