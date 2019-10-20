#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int L = 51; 
void solve() {
    int n; ll m;
    cin >> n >> m;
    vector<int> z(L), p(L);
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        for (int i = 0; i < L; i++) {
            int k = (x>>i) & 1;
            z[i] += k^1;
            p[i] += k;
        }
    }
    vector<ll> mi(L+1);
    mi[0] = 0;
    for (int i = 0; i < L; i++) {
        mi[i+1] = mi[i] + min(z[i],p[i]) * (1ll<<i);
    }

    if (mi[L] > m) {
        cout << -1; return;
    }
    ll sum = 0;
    ll res = 0;
    for (int i = L-1; i >= 0; i--) {
        ll k = 1ll << i;
        if (sum + k*z[i] + mi[i] <= m) {
            sum += k*z[i];
            res |= k;
        } else {
            sum += k*p[i];
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
        cout << "\n";
    }
    fflush(stdout);
}
