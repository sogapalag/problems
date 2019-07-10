#include <bits/stdc++.h>

using namespace std;

using ll=long long;

void solve() {
    ll n, mod;
    cin >> n >> mod;
    vector<ll> pref(n);
    ll crt = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        x %= mod;
        crt = (crt + x) % mod;
        pref[i] = crt;
    }
    set<ll> s;
    s.insert(0); s.insert(mod);
    ll res = 0;
    for (int i = 0; i < n; i++) {
        ll up = *s.upper_bound(pref[i]);
        ll tmp = (pref[i] - up + mod) % mod;
        res = max(res, tmp);
        s.insert(pref[i]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
