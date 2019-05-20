#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n+1);
    a[0] = {0,0};
    for (int i = 1; i <= n; i++) {
        cin >> a[i].second >> a[i].first;
        a[i].first++;
    }
    sort(a.begin(), a.end());
    vector<int> dp(n+1, 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1]; 
        auto it = upper_bound(a.begin(), a.end(), make_pair(a[i].second, a[i].second));
        int k = it - a.begin();
        dp[i] = max(dp[i], dp[k-1] + a[i].first - a[i].second);
    }
    cout << dp[n] * 100;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
