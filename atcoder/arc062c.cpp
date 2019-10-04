#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}

void solve() {
    int n; cin >> n;
    ll x, y;
    cin >> x >> y;
    for (int _ = 1; _ < n; _++) {
        ll p,q;
        cin >> p >> q;
        ll lim = 2e18/(max(p,q));
        ll t = bs_first<ll>(1, lim, [&](ll t){
                return p*t>=x && q*t>=y;
                });
        x = p*t;
        y = q*t;
    }
    cout << (x+y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
