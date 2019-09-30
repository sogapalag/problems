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
    ll x; cin >> x;
    ll n = bs_first<ll>(1, 100000, [&](ll n){
            return n*(n+1)/2 >= x;
            });
    cout << n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
