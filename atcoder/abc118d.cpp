#include <bits/stdc++.h>

using namespace std;


// dp[n] with n match, max length
void solve() {
    int n,m;
    cin >> n >> m;
    int cost[10] = {2048, 2,5,5,4,5,6,3,7,6};
    vector<int> a;
    while (m--) {
        int x; cin >> x;
        a.push_back(x);
    }
    sort(a.begin(), a.end(), greater<int>());
    vector<int> dp(n+20, -111);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
        for (int x: a) {
            int k = i + cost[x];
            dp[k] = max(dp[k], dp[i]+1);
        }
    }
    string res;
    while (n) {
        for (int x: a) {
            if (n < cost[x]) continue;
            if (dp[n - cost[x]] + 1 == dp[n]) {
                res += ('0'+x);
                n -= cost[x];
                break;
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
