#include <bits/stdc++.h>

using namespace std;
const int n = 10; 
int a[n][n];
double dp[n][n];

// simple prob formula
void solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    vector<pair<int, int>> pth;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < n; j++) {
            pth.emplace_back(i<<1,j);
        }
        for (int j = n-1; j >= 0; j--) {
            pth.emplace_back(i<<1|1,j);
        }
    }
    dp[0][0] = 0;
    for (int j = 1; j <= 6; j++) {
        dp[0][j] = 6;
    }
    for (int k = 7; k < n*n; k++) {
        double sum = 0;
        for (int x = 1; x <= 6; x++) {
            int i,j;
            tie(i,j) = pth[k-x];
            double tmp = dp[i][j];
            if (a[i][j]) {
                i -= a[i][j];
                tmp = min(tmp, dp[i][j]);
            }
            sum += tmp;
        }
        int i,j;
        tie(i,j) = pth[k];
        dp[i][j] = 1.0 + sum/6.0;
    }
    cout << fixed << setprecision(10) << dp[9][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
