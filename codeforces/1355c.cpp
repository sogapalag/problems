#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll a,b,c,d;
    cin >> a >> b >> c >> d;
    ll tot = (b-a+1)*(c-b+1)*(d-c+1);
    //    c---d
    //  l---r
    auto f = [&](ll l, ll r){
        ll res = 0;
        r = min(r, d);
        res += max(0ll, min(c,r) - l+1) * (d-c+1);
        l = max(l, c+1);
        if (l <= r) {
            ll x = d-l+1;
            ll y = d-r+1;
            res += (x+y)*(r-l+1)/2;
        }
        return res;
    };
    for (int y = b; y <= c; y++) {
        tot -= f(a+y, b+y);
    }
    cout << tot << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
