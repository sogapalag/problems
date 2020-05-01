#include <bits/stdc++.h>

using namespace std;
using ll=long long;

pair<ll,int> dp[2][512];
#define cnt first
#define b second
// dp[red] : (#, blue). since always better with more #, than with more blue
void solve() {
    int n,m;
    cin >> n >> m;
    int crt = 0;
    memset(dp[crt], 0xc0, sizeof dp[crt]);
    dp[0][0] = {0, 0};
    for (int _ = 0; _ < n; _++) {
        int nxt = crt^1;
        memset(dp[nxt], 0xc0, sizeof dp[nxt]);
        int x,y;
        cin >> x >> y;
        for (int i = max(1, m-y); i < m && i <= x; i++) {
            for (int r = 0; r < m; r++) {
                auto& p = dp[crt][r];
                dp[nxt][(r+x-i)%m] = max(dp[nxt][(r+x-i)%m], 
                        {p.cnt+1 + (r+x-i)/m + (p.b+y-(m-i))/m, (p.b+y-(m-i))%m});
            }
        }
        for (int r = 0; r < m; r++) {
            auto& p = dp[crt][r];
            dp[nxt][(r+x)%m] = max(dp[nxt][(r+x)%m],
                    {p.cnt + (r+x)/m + (p.b+y)/m, (p.b+y)%m});
        }
        crt ^= 1;
    }
    ll res = 0;
    for (int i = 0; i < m; i++) {
        res = max(res, dp[crt][i].cnt);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
