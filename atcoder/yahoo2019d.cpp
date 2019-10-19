#include <bits/stdc++.h>

using namespace std;

using ll=long long;

ll dp[5];
// note op is form  0..0 even odd even 0..0 five segs, even!=0
// let dp[j] be crt seg [.
void solve() {
    int n; cin >> n;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        int k = (x&1);
        // decide x in which seg
        dp[4] = min(dp[4] + x, dp[3] + x);          //  0
        if(x)dp[3] = min(dp[3] + k, dp[2] + k);     //  even
        else dp[3] = min(dp[3] + 2, dp[2] + 2);     //  not inf, 0 still could even, but cost is 2
        dp[2] = min(dp[2] + (k^1), dp[1] + (k^1));  //  odd
        if(x)dp[1] = min(dp[1] + k, dp[0] + k);     //  even
        else dp[1] = min(dp[1] + 2, dp[0] + 2);     
        dp[0] = dp[0] + x;                          //  0
        // here is important, since [) we can close some segs
        for (int i = 1; i < 5; i++) {
            dp[i] = min(dp[i], dp[i-1]);
        }
        //for (int i = 0; i < 5; i++) {
        //    cout << dp[i] << ' ';
        //}cout << "\n";
    }
    ll res = 1ll<<60;
    for (int i = 0; i < 5; i++) {
        res = min(res, dp[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
