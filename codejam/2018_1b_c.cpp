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
    int n; cin >> n;
    vector<array<int,2>> g(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        --x;--y;
        g[i] = {x,y};
    }
    vector<ll> A(n);
    ll tot = 0;
    for (auto& x: A) {
        cin >> x;
        tot += x;
    }

    auto ck = [&](ll T){
        auto a = A;
        a[0] -= T;
        // n(cycle-len) round
        for (int _ = 0; _ < n; _++) {
            for (int i = 0; i < n; i++) {
                ll x = a[i];
                if (x < 0) {
                    // might 2^n overflow
                    if (x < -tot) return false;
                    // dept can only be pushed
                    a[i] = 0;
                    for (int v:g[i]) {
                        a[v] += x;
                    }
                }
            }
        }
        for (ll x:a) if (x<0) return false;
        return true;
    };
    ll res = bs_last<ll>(0, tot+1, ck);
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
