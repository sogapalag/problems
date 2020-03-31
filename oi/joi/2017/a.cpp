#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, q;
    cin >> n >> q;
    ll S, T;
    cin >> S >> T;
    n++;
    vector<ll> a(n);
    for (auto& x: a) cin >> x;
    ll res = 0;
    auto f = [&](ll x){
        return x > 0 ? -x*S : -x*T;
    };
    // delta
    for (int i = n-1; i >= 1; i--) {
        a[i] -= a[i-1];
        res += f(a[i]);
    }
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        r++;
        res -= f(a[l]);
        res += f(a[l]+=x);
        if (r < n) {
            res -= f(a[r]);
            res += f(a[r]-=x);
        }
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
