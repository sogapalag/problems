#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (auto& x: a) cin >> x;
    vector<ll> l(n+2), r(n+2); // lower/upper bound
    for (int i = n; i >= 0; i--) {
        l[i] = a[i] + (l[i+1]+1)/2;
        r[i] = a[i] + r[i+1];
        if(i < 60) r[i] = min(r[i], 1ll<<i); // can (n*1e8 = 1e13)
        if (l[i] > r[i]) {
            cout << -1; return;
        }
    }
    ll res = 0;
    for (int i = 0; i <= n; i++) {
        res += r[i];
        r[i+1] = min(r[i+1], (r[i]-a[i])*2ll);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
