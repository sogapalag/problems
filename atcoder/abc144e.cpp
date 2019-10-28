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
    vector<int> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());
    ll res = bs_first<ll>(0, 1e12+10, [&](ll t){
            ll need = 0;
            for (int i = 0; i < n; i++) {
                need += max(0ll, a[i] - t/b[i]);
            }
            return need <= K;
            });
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
