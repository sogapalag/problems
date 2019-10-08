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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        x /= 100;
    }
    sort(a.begin(), a.end(),greater<int>());
    ll x, y, u, v;
    cin >> x >> u;
    cin >> y >> v;
    if (x < y) {
        swap(x,y);
        swap(u,v);
    }
    ll K; cin >> K;

    ll lcm = u*v / __gcd(u,v);
    int res = bs_first<int>(1, n+1, [&](int i){
            int c0 = i/u;
            int c1 = i/v;
            int cc = i/lcm;
            c0-=cc; c1-=cc;
            int j = 0;
            ll sum = 0;
            for (int _ = 0; _ < cc; _++) {
                sum += a[j++]*(x+y);
            }
            for (int _ = 0; _ < c0; _++) {
                sum += a[j++]*x;
            }
            for (int _ = 0; _ < c1; _++) {
                sum += a[j++]*y;
            }
            return sum >= K;
            });
    if (res > n) res = -1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
