#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,s;
        cin >> x >> s;
        x--;
        a[i] = {x,s};
    }
    vector<int> dp(m+1); // cost to cover [i..m]
    for (int i = 0; i <= m; i++) {
        dp[i] = m-i;
    }
    for (int i = m-1; i >= 0; i--) {
        for (auto& p: a) {
            int x,s;
            tie(x,s) = p;
            int l = x-s;
            int r = x+s;
            if (l <= i && i <= r) { // i is covered
                dp[i] = min(dp[i], dp[i+1]);
            } else if (i < l) { // use some right-part to extend
                int d = l-i;
                r += d+1;
                int cost = r > m? 0 : dp[r];
                dp[i] = min(dp[i], cost + d);
            }
        }
    }
    cout << dp[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
