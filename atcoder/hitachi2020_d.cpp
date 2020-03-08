#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// let a++, b++
// by consider a1(a0t+b0)+b1 < a0(a1t+b1) + b0  <=> (a1-1)*b0 < (a0-1)*b1
// so we should take as the order. dp[i] as min time taken i items. a naive O(n^2) dp
// key optim: when a>1, only log state, since 2^. grow exp. and for a=1, it's just plus b.
void solve() {
    int n, T;
    cin >> n >> T;
    vector<pair<int, int>> a;
    vector<int> bs;
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        if (x) a.emplace_back(x,y);
        else bs.emplace_back(y);
    }
#define fi first
#define se second
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
        return (u.se+1)*1ll*v.fi < (v.se+1)*1ll*u.fi;
    });
    sort(bs.begin(), bs.end());
    n = a.size();

    const int L = 31; 
    vector<ll> dp(L, 1ll<<31);
    dp[0] = 1;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        tie(x,y) = a[_];
        x++;y++;
        for (int i = L-1; i >= 0; i--) {
            dp[i+1] = min(dp[i+1], x * dp[i] + y);
        }
    }
    T++;
    int res = 0;
    for (int i = 0; i < L; i++) {
        int cnt = i;
        ll t = dp[i];
        if (t > T) continue;
        for (int y: bs) {
            y++;
            if (t + y <= T) {
                t += y;
                cnt++;
            } else break;
        }
        res = max(res, cnt);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
