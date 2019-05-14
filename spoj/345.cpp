#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 111;

int a[N];
int sum[N][N];
int dp[N][N];

void solve() {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        sum[1][0] = 0;
        for (int i = 1; i <= n; i++) {
            sum[1][i] = sum[1][i-1] + a[i];
        }
        for (int i = 2; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                sum[i][j] = sum[1][j] - sum[1][i-1];
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                sum[i][j] = (sum[i][j] + 100) % 100;
            }
        }
        memset(dp, INF, sizeof dp);
        for (int d = 0; d < n; d++) {
            for (int i = 1; i <= n-d; i++) {
                if (!d) {
                    dp[d][i] = 0;
                    continue;
                }
                for (int j = i; j < i+d; j++) {
                    dp[d][i] = min({dp[d][i], dp[j-i][i] + dp[i+d-j-1][j+1]
                            + sum[i][j] * sum[j+1][i+d]});
                }
            }
        }
        cout << dp[n-1][1] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
