#include <bits/stdc++.h>

using namespace std;

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
using ll=long long;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> d(n-1);
    for (int i = 1; i < n; i++) {
        d[i-1] = a[i] - a[i-1];
    }
    // for ceil(x/(k+1)) <= avg  <=> k >= ceil(x/avg) -1
    auto ck = [&](int avg){
        ll need = 0;
        for (int x:d) {
            need += (x+avg-1)/avg - 1;
        }
        return need <= k;
    };
    int res = bs_first<int>(1, 1e9+10, ck);
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
