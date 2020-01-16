#include <bits/stdc++.h>

using namespace std;
using ll=long long;
ll cnt[9];
const ll D = 10; 
ll dfs(ll w, ll i) {
    if (i == 0) return w;
    ll r = min(cnt[i], w/i);
    ll l = max(0ll, r-D);
    ll delta = w;
    for (ll k = l; k <= r; k++) {
        delta = min(delta, dfs(w - k*i, i-1));
        //cerr<<delta<<','<<'k'<<k<<'i'<<i<<'\n';
    }
    return delta;
}
void solve() {
    ll W; cin >> W;
    for (int i = 1; i <= 8; i++) {
        cin >> cnt[i];
    }
    //cout << W-dfs(W, 8);
    const int L = 840;  // LCM
    ll got = 0;
    for (int i = 1; i <= 8; i++) {
        ll b = L/i;
        // should reserve >=b. so might 2L. total 16L
        ll could = max((cnt[i] - b) / b, 0ll);
        got += could * L;
        cnt[i] -= could * b;
    }
    got = min(got, W/L*L);
    bitset<L*17> dp;
    dp[0] = 1;
    for (int i = 1; i <= 8; i++) {
        for (int _ = 0; _ < cnt[i]; _++) {
            dp |= dp<<i;
        }
    }
    for (int x = 16*L; x >= 0; x--) {
        if (dp[x] && got+x<=W) {
            cout << got+x; return;
        }
    }
}
// test is weak, should include below
// 843
// 840 0 0 0 0 0 0 105
// should output 843
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
