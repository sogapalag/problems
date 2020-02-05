#include <bits/stdc++.h>

using namespace std;

using ll=long long;
const int N = 5022; 
ll dp[N][N];
deque<int> mx[N];
// a extending/growing slider. since [use j][at i] dep on max [use j-1][at [i-lim..i)]
void solve() {
    int n, lim, m;
    cin >> n >> lim >> m;

    memset(dp, 0xef, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i <= m; i++) {
        mx[i].push_back(0);
    }

    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        int l = max(0, i - lim);
        for (int j = m; j >= 0; j--) {
            if (j > 0) {
                while (l >= 0 && l > mx[j-1].front()) mx[j-1].pop_front();
                int k = mx[j-1].front();
                dp[j][i] = dp[j-1][k] + x;
            }
            while (!mx[j].empty() && dp[j][mx[j].back()] <= dp[j][i]) {
                mx[j].pop_back();
            }
            mx[j].push_back(i);
            //s[j].assign(i, s[j-1].query(l, i) + x);
        }
    }

    ll res = -1;
    for (int i = n-lim+1; i <= n; i++) {
        res = max(res, dp[m][i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
