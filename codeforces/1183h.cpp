#include <bits/stdc++.h>

using namespace std;

long long dp[101][27];

void solve() {
    int n; long long K;
    cin >> n >> K;
    string s; cin >> s;
    memset(dp, 0, sizeof dp);
    dp[0][26] = 1; // for empty
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        for (int j = i; j >= 0; j--) {
            dp[j+1][c] = 0; // for avoid dup. cnt
            for (int k = 0; k <= 26; k++) {
                dp[j+1][c] += dp[j][k];
            }
        }
    }
    long long sum = 0, cost=0;
    for (int i = n; i >= 0; i--) {
        for (int k = 0; k <= 26; k++) {
            if (K - sum <= dp[i][k]) {
                cost += (K-sum) * (n - i);
                sum = K; 
                {
                    cout << cost; return;
                }
            }
            sum += dp[i][k];
            cost += dp[i][k] * (n-i);
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
