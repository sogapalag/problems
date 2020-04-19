#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; ll D;
    cin >> n >> D;
    ll d = D;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (int i = n-1; i >= 0; i--) {
        ll x = a[i];
        d = d/x*x;
    }
    cout << d << "\n";
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
