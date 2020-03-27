#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,A,B;
    cin >> n >> A >> B;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    const int L = 42; 
    if (A == 1) {
        vector<int> dp(n + 1);
        // [i]: min valid(layer:#seg)
        ll res = 0;
        for (int k = L; k >= 0; k--) {
            fill(dp.begin(), dp.end(), 2048);
            dp[0] = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j < i; j++) {
                    ll x = sum[i]-sum[j];
                    //if (x>>k&1) continue;
                    //if (((x|res)>>(k+1)) > (res>>(k+1))) continue;
                    if ((x|res)>>k > res>>k) continue;
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
            if (dp[n] > B) res |= 1ll<<k;
        }
        cout << res;
    } else {
        bool dp[102][102];
        // [layer:#seg][..i] true iff this bit still all zero, and with prefix won't be larger
        ll res = 0;
        for (int k = L; k >= 0; k--) {
            memset(dp, 0, sizeof dp);
            dp[0][0] = 1;
            for (int _ = 0; _ < B; _++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 0; j < i; j++) {
                        ll x = sum[i]-sum[j];
                        //if (x>>k&1) continue;
                        //if (((x|res)>>(k+1)) > (res>>(k+1))) continue;
                        if ((x|res)>>k > res>>k) continue; // equiv above
                        dp[_+1][i] |= dp[_][j];
                    }
                }
            }
            for (int _ = A; _ <= B; _++) {
                if (dp[_][n]) goto nxt;
            }
            res |= 1ll<<k;
            nxt:;
        }
        cout << res;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
