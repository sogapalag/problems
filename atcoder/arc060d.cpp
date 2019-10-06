#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll f(ll i, ll n) {
    ll x = n;
    ll sum = 0;
    while (x) {
        sum += x%i;
        x /= i;
    }
    return sum;
}

void solve() {
    ll n, s;
    cin >> n >> s;
    if (n == s) {
        cout << (n+1); return;
    }
    if (n < s) {
        cout << -1; return;
    }
    for (ll i = 2; i*i <= n; i++) {
        if (f(i,n) == s) {
            cout << i; return;
        }
    }
    ll res = 1ll<<55;
    // n = j*i + q; j <= sq(n)
    for (ll j = 1; j*j <= n; j++) {
        if ((n-s)%j) continue;
        ll i = (n-s)/j + 1;
        if (f(i, n) == s) {
            res = min(res, i);
        }
    }
    if (res > (1ll<<53)) res = -1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
