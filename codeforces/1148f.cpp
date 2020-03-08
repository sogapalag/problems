#include <bits/stdc++.h>

using namespace std;
using ll=long long;

int hbit(ll n) {
    return 63 - __builtin_clzll(n);
}
bool odd(ll n) {
    return __builtin_popcountll(n)&1;
}
bool same(ll x, ll y) {
    return (x<0&&y<0) || (x>0&&y>0);
}
const int L = 62; 

void solve() {
    int n; cin >> n;
    vector<pair<int,ll>> g[L];
    ll tot = 0;
    for (int _ = 0; _ < n; _++) {
        int x; ll m;
        cin >> x >> m;
        g[hbit(m)].emplace_back(x,m);
        tot += x;
    }
    ll res = 0;
    // make each group has opposite sign of tot.
    for (int i = 0; i < L; i++) {
        ll now = 0;
        for (auto& _: g[i]) {
            int x; ll m;
            tie(x, m) = _;
            if (odd(m & res)) x *= -1;
            now += x;
        }
        if (same(tot, now)) res |= 1ll<<i;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
