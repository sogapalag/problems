#include <bits/stdc++.h>

using namespace std;

using ll = long long ;

ll lcm(ll a, ll b) {
    ll g = __gcd(a,b);
    return (long double)a/g * b;
}


void solve() {
    int n; cin >> n;
    ll res = 1;
    for (int _ = 0; _ < n; _++) {
        ll x; cin >> x;
        res = lcm(res, x);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
