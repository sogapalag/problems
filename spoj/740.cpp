#include <bits/stdc++.h>

using namespace std;

const int N = 2002; 

int v[N];
int dp[N][N];

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int d = 0; d < n; d++) {
        for (int i = 1; i <= n-d; i++) {
            dp[d][i] = d == 0 ? v[i]*(n-d) : 
                max(dp[d-1][i] + v[i+d]*(n-d), dp[d-1][i+1] + v[i]*(n-d));
        }
    }
    cout << dp[n-1][1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
