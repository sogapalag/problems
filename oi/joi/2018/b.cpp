#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// by a sort, note if fix l,r, mid obvious take all
// split, consider one end contribution, e.g. left, ai+bi + ..+ b +..
void solve() {
    int n; cin >> n;
    vector<pair<ll,ll>> c(n);
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i].first >> c[i].second;
    }
    sort(c.begin(), c.end());
    for (int i = 0; i < n; i++) {
        tie(a[i],b[i]) = c[i];
    }
    ll res = *max_element(b.begin(), b.end());
    vector<ll> pref(n);
    pref[0] = a[0] + b[0];
    for (int i = 1; i < n; i++) {
        pref[i] = max(pref[i-1] + b[i], a[i] + b[i]);
    }
    ll suff = -a[n-1] + b[n-1];
    for (int i = n-2; i >= 0; i--) {
        res = max(res, pref[i] + suff);
        suff = max(suff + b[i], -a[i] + b[i]);
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
