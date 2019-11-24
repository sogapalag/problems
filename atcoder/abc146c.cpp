#include <bits/stdc++.h>

using namespace std;
using ll=long long;

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

void solve() {
    ll a,b,x;
    cin >> a >> b >> x;
    ll res = bs_last<ll>(1, 1e9+1, [&](ll n){
            auto s = to_string(n);
            ll cost = n*a + b*(s.size());
            return cost <= x;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
