#include <bits/stdc++.h>

using namespace std;

const int N = 502; 
int dp[N][N]; // [l][r] can be merge into one number x
int f[N][N]; // min-len [l][r]

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; i++) {
        dp[i][i+1] = a[i];
        f[i][i+1] = 1;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i+len <= n; i++) {
            int r = i+len;
            // iter mid
            for (int m = i+1; m < r; m++) {
                int x = dp[i][m];
                int y = dp[m][r];
                f[i][r] = min(f[i][r], f[i][m] + f[m][r]);
                if (x && y && x == y) {
                    dp[i][r] = x + 1;
                    f[i][r] = 1;
                    break;
                }
            }
        }
    }
    cout << f[0][n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
