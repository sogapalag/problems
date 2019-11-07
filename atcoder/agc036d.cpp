#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 512; 
int a[N][N];
ll pos[N][N], neg[N][N];
ll dp[N][N];

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i!=j) cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            pos[i][j] += pos[i][j+1] + a[i][j];
            neg[i][j] += neg[i][j+1] + a[j][i];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            ll sum = 0;
            for (int x = i+1; x <= n; x++) {
                //sum += pos[x][j] - pos[x][i];
                sum += -pos[x-1][j];
                sum += neg[x-1][i];
                dp[x][i] = min(dp[x][i], dp[i][j] + sum);
            }
        }
    }
    ll res = 1ll<<60;
    for (int j = 0; j <= n; j++) {
        res = min(res, dp[n][j]);
    }
    for (int i = 0; i < n; i++) {
        res += pos[i][0];
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
