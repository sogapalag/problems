#include <bits/stdc++.h>

using namespace std;

const int N = 1000;
const int Q = 600;
const int QQ = 3600; 

double dp[N][QQ];

int ans[Q][QQ];

void solve() {
    memset(dp, 0, sizeof dp); 
    dp[0][0] = 1.0;
    for (int i = 1; i < Q; i++) {
        for (int j = i; j <= 6*i; j++) {
            for (int x = 1; x <= 6 && x <= j; x++) {
                dp[i][j] += dp[i-1][j-x];
            }
            dp[i][j] /= 6.0;
        }
        //int K = int(3.5*i);
        //cout << i << ' ' << K << ' ' << dp[i][K] << '\n';
    }
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < QQ; j++) {
            ans[i][j] = (int)floor(dp[i][j] * 100);
        }
    }
    int T; cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        if (n >= Q || k < n || k > 6*n) cout << "0\n";
        else{
            cout << ans[n][k] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
