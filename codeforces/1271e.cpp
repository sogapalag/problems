#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    if (l>=r) return l-1;
    //assert(l < r);
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
void solve() {
    ll n, k;
    cin >> n >> k;
    ll m = n/2;

    int h = 63-__builtin_clzll(n);
    auto prefix = [&](ll y){
        if (y > n) return 0ll;
        int j = 63-__builtin_clzll(y);
        if ((n>>(h-j) > y)) {
            return (1ll<<(h-j+1)) - 1;
        } else if ((n>>(h-j)) == y){
            return (1ll<<(h-j)) + (n - (y<<(h-j)) );
        } else {
            return (1ll<<(h-j)) - 1;
        }
    };

    ll y0 = bs_last<ll>(1, m+1, [&](ll p){
            ll y = p<<1;
            return prefix(y) + prefix(y|1) >= k;
            });
    ll y1 = bs_last<ll>(0, m+1, [&](ll p){
            ll y = (p*2)|1;
            return prefix(y) >= k;
            });
    ll y = 1;
    if (y0>0) y = max(y, y0<<1);
    y = max(y, y1<<1|1);
    cout << y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
