#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<long long> dp(n+1);
    vector<long long> dn(n+1);
    dp[1] = a[1]; dn[1] = -a[1];
    for (int i = 2; i <= n; i++) {
        dp[i] = max(dp[i-1]+a[i], dn[i-1]-a[i]);
        dn[i] = max(dp[i-1]-a[i], dn[i-1]+a[i]);
    }
    cout << dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
