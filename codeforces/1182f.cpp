#include <bits/stdc++.h>

using namespace std;

using ll=long long;

ll a, b, p, q;

ll calc(ll a, ll b, ll c, ll n) {
    if (!n) return 0;
    ll res = (a/c) * n*(n-1)/2 + (b/c) * n;
    a %= c; b %= c;
    ll t = a*n+b;
    return res + calc(c, t%c, a, t/c);
}

ll cnt(ll xl, ll xr, ll yl, ll yr) {
    return calc(p, p*xl+q-yl, q, xr-xl+1) - calc(p, p*xl+q-yr-1, q, xr-xl+1);
}

// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = (l+r)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}


// px = y mod q,
// first bs on y, [q/2 +- dy],
// second bs on x, fix [q/2 +- d], search [a, x] a valid point.
//
// note the calc is def as, \sum_{i=0}^{n-1}  \floor {(a*i+b) / c}
// thus in cnt, for each i, A_i - B_i = 0 or 1, exactly whether px = y in the given region.
void solve() {
    cin >> a >> b >> p >> q;    
    ll d = bs_first<ll>(0, q/2 + 1, [&](ll x){
            return cnt(a, b, q/2 - x, (q+1)/2 + x) > 0;
            });
    ll res = bs_first<ll>(a, b + 1, [&](ll x){
            return cnt(a, x, q/2 - d, (q+1)/2 + d) > 0;
            });
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
