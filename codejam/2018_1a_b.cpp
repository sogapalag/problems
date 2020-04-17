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
    int R,B,n;
    cin >> R >> B >> n;
    vector<int> M(n), k(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> M[i] >> k[i] >> b[i];
    }
    auto ck = [&](ll T){
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = min((ll)M[i], T<b[i]? 0ll : (T-b[i])/k[i]);
        }
        sort(a.begin(), a.end(), greater<int>());
        ll sum = 0;
        for (int i = 0; i < R; i++) {
            sum += a[i];
        }
        return sum >= B;
    };
    ll res = bs_first<ll>(0, (1e18)+(1e10), ck); // kB+b
    cout << res << "\n";
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
