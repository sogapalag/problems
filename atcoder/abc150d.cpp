#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; ll m;
    cin >> n >> m;
    vector<ll> a(n);
    ll lcm = 1;
    for (auto& x: a) {
        cin >> x;
        ll g = __gcd(lcm, x);
        lcm = lcm * x / g;
        if (lcm > 2*m) {
            cout << 0; return;
        }
    }
    ll z = lcm/2;
    // ck
    for (ll x: a) {
        if (z%x != x/2) {
            cout << 0; return;
        }
    }
    ll res = m/lcm + (m%lcm >= z);
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
