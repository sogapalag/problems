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
    int n; ll m;
    cin >> n >> m;
    vector<ll> a(n);
    vector<ll> sum(n+1);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end(), greater<ll>());
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }

    ll C,S;
    // (..+..) * (..+..), fix left, bs j (0..n) might be easier, thus don't think how many a[i], (sum) coeff
    // another way.FFT omit
    auto ck = [&](ll x){
        ll cnt = 0;
        S = 0;
        for (int i = 0; i < n; i++) {
            if (a[i]*2<x)break;
            int j = bs_last<int>(i, n, [&](int j){
                    return a[i]+a[j] >= x;
                    });
            cnt += 2*(j-i)+1;
            S += a[i] * (2*(j-i)+2) + (sum[j+1]-sum[i+1]) * 2;
        }
        C = cnt;
        return cnt >= m;
    };
    ll x = bs_last<ll>(0, 2e5+10, ck);
    ck(x);
//cout << S << "\n";
    ll res = S - (C-m)*x;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
