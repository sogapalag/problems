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
// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}
ll f(ll x){return x*(x+1)/2;}
ll f(ll x, ll y) {
    return (x+y)*(y-x+1)/2;
}
ll g(ll x, ll y) {
    return (x+y)*((y-x)/2+1)/2;
}
void solve() {
    ll l, r;
    cin >> l >> r;
    ll n = 1;
    // use r till switch
    if (r > l) {
        ll x = bs_first<ll>(1, 2e9+10, [&](ll x){
                return l >= r-f(x);
                });
        r -= f(x);
        n = x+1;
    }
    if (r < 0) {
        r += n-1;
        n--;
        cout << n-1 << ' ' << l << ' ' << r << '\n';
        return;
    }

    // use l till switch
    ll x = bs_last<ll>(n, 2e9+10, [&](ll x){
            return l - f(n,x) >= r;
            });
    if (n <= x) l -= f(n, x);
    n = x + 1;

    // remain form:
    // n, n+1
    // n+2, n+3
    // ..
    x = bs_last<ll>(1, 2e9+10, [&](ll x){
            ll z = f(x-1)*2 + n*x;
            return l - z >= 0 && r - z - x >= 0;
            });
    if (1 <= x) {
        ll z = f(x-1)*2+n*x;
        l -= z;
        r -= z + x;
        n += x*2;
    }
    // still l?
    if (l >= n) {
        l -= n; n++;
    }

        cout << n-1 << ' ' << l << ' ' << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
