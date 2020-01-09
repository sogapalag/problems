#include <bits/stdc++.h>

using namespace std;

const int N = 52; 
double dp[N][N][N];
double fac[N];
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(m);
    for (auto& x: a) {
        cin >> x;
    }
    fac[0]=1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i-1]*i;
    }
    dp[0][0][0] = 1;
        for (int j = 0; j < m; j++) {
    for (int i = 0; i <= n; i++) {
            for (int k = 0; k <= n; k++) {
                // put d at j
                for (int d = 0; i+d <= n; d++) {
                    dp[i+d][j+1][max(k, (d+a[j]-1)/a[j])] += dp[i][j][k] / fac[d];
                }
            }
        }
    }
    double res = 0, sum = 0;
    for (int i = 0; i <= n; i++) {
        res += i * dp[n][m][i];
        sum += dp[n][m][i];
    }
    res /= sum;
    cout << fixed << setprecision(10) << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
