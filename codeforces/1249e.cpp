#include <bits/stdc++.h>

using namespace std;

const int N = 200005; 
int dp[N][2];

void solve() {
    int n,c;
    cin >> n >> c;
    vector<int> a(n-1), b(n-1);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    dp[0][0] = 0; dp[0][1] = c;
    for (int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i-1][0] + a[i-1], dp[i-1][1] + a[i-1]);
        dp[i][1] = min(dp[i-1][0] + c + b[i-1], dp[i-1][1] + b[i-1]);
    }
    for (int i = 0; i < n; i++) {
        cout << min(dp[i][0], dp[i][1]) << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
