#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    reverse(a.begin(), a.end());
    vector<bool> dp(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i]==1) dp[i]=true;
        else if (i>0&&dp[i-1]&&a[i-1]+1==a[i]) dp[i] = true;

        if (dp[i] && a[i]==k) cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
