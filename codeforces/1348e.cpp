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

// note we can actually care dp[r] true/false, i.e. can use #red for one r+b
// since although two (r+b), we can treat it as one (r+b) (note, not meanning it's valid, but ajust valid combi. is fine) 
// thus we can treat find any (r+b) valid, remain can treat as same group, since there must be some valid corresponding.
// key optim: dp[i] contribute to a range i+[l..r], optim by delta.
void fast() {
    int n,m;
    cin >> n >> m;
    vector<bool> dp(m);
    vector<int> cnt(2*m);
    ll sx = 0, sy = 0;
    dp[0] = true;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        sx += x; sy += y;
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < m; i++)if(dp[i]) {
            int l = max(1, m-y);
            int r = min(m-1, x);
            if (l <= r) {
                cnt[i+l]++; cnt[i+r+1]--;
            }
        }
        for (int i = 1; i < 2*m; i++) {
            cnt[i] += cnt[i-1];
            if (cnt[i] > 0) dp[i%m] = true;
        }
    }
    ll res = 0;
    for (int i = 0; i < m; i++)if(dp[i]) {
        res = max(res, (i>0) + (sx-i)/m + (sy-(m-i)%m)/m );
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fast();
    //solve();
    return 0;
}
