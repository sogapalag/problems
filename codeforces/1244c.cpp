#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n, p, w, d;
    cin >> n >> p >> w >> d;
    ll g = __gcd(w,d);
    if (p % g != 0) {
        cout << -1; return;
    }
    p/=g,w/=g,d/=g;

    // key y<w, since y*w = x*d, thus (x+y) become less. since we wanna which <= n
    for (int y = 0; y < w && y <= n; y++) {
        ll rem = p - y*d;
        if (rem < 0) continue;
        if (rem % w != 0) continue;
        ll x = rem/w;
        if (x + y > n) continue;
        cout << x << ' ' << y << ' ' << (n-x-y); return;
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
