#include <bits/stdc++.h>

using namespace std;
using ll=long long;
template <typename T=double>
pair<T,T> ternary(T l, T r, function<T(T)> f, bool V=true) {
    while (r - l > 2) {
        T m0 = l + (r-l)/3;
        T m1 = r - (r-l)/3;
        T f0 = f(m0);
        T f1 = f(m1);

        if ((f0 < f1) ^ V) {
            l = m0;
        } else {
            r = m1;
        }
    }
    return {l, f(l)};
}

// f(h) is V. so ternary
void solve() {
    ll n,A,R,M;
    cin >> n >> A >> R >> M;
    M = min(M, A+R); // might M > 
    vector<ll> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    auto f = [&](ll h){
        int i = lower_bound(a.begin(), a.end(), h) - a.begin();
        ll x = i*h - sum[i];
        ll y = (sum[n]-sum[i]) - (n-i)*h;
        ll z = min(x,y);
        x -= z; y -= z;
        return z*M + x*A + y*R;
    };
    ll l, x;
    tie(l, x) = ternary<ll>(0, 1e9+10, f);
    //cerr<<l<<endl;
    ll res = min({x, f(l+1), f(l+2)});
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
