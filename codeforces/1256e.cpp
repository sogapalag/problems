#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int N = 2e5+10; 
ll dp[N][3]; // cut before i:0,1,>=2

// note those sets don't overlap, so find cut pos
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = {x, i};
    }
    sort(a.begin(), a.end());
    memset(dp, 0xa0, sizeof dp);
    dp[0][0] = 0;
    for (int i = 1; i+3 <= n; i++) {
        dp[i][0] = dp[i-1][2] + a[i].first - a[i-1].first;
        dp[i][1] = dp[i-1][0];
        dp[i][2] = max(dp[i-1][1], dp[i-1][2]);
    }
    ll x = max({dp[n-3][0], dp[n-3][1], dp[n-3][2]});
    ll res = a[n-1].first - a[0].first - x;
    vector<int> co(n);
    int cnt = 1;
    for (int i = n-1; i >= n-3; i--) {
        co[a[i].second] = cnt;
    }
    for (int i = n-3; i >= 1; i--) {
        // 0,1,2 order may cause len<3 when both=x
        if (dp[i][2] == x) {
            co[a[i-1].second] = co[a[i-2].second] = cnt;
            i--;
        } else if (dp[i][1] == x) {
            co[a[i-1].second] = cnt;
        } else if (dp[i][0] == x) {
            cnt++;
            x -= a[i].first - a[i-1].first;
            co[a[i-1].second] = cnt;
        }
    }
    cout << res << ' ' << cnt << "\n";
    for (auto& x: co) {
        cout << x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
