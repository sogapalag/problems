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
    int n; ll K;
    cin >> n >> K;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    
    auto ck = [&](ll ta){
        // can two-pointer, omit
        ll cnt = 0;
        for (int i = 1; i < n; i++) {
            ll x = a[i];
            if (x > 0) {
                int k = bs_first<int>(0, i, [&](int k){
                        return a[k]*x > ta;
                        });
                cnt += k;
            } else {
                int k = bs_first<int>(0, i, [&](int k){
                        return a[k]*x <= ta;
                        });
                cnt += i-k;
            }
        }
        return cnt >= K;
    };
    ll res = bs_first<ll>(-1e18-10, 1e18+10, ck);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
