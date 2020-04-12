#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n, l, r;
    cin >> n >> l >> r; --l;
    auto f = [&](ll i){
        vector<int> a;
        a.push_back(i);
        for (int x = i+1; x < n; x++) {
            a.push_back(x);
            a.push_back(i);
        }
        a.push_back(n);
        if (i+1 == n) a.push_back(1);
        return a;
    };
    for (ll s = 0, e = 0, i = 1; i < n; i++) {
        s = e;
        e += 2*(n-i) + (i+1==n);
        if (e <= l || r <= s) continue;
        ll L = max(l, s), R = min(r, e);
        auto a = f(i);
        assert((int)a.size() == e-s);
        for (int k = L-s; k < R-s; k++) {
            cout << a[k] << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
