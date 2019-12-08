#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// note pick i*a, coeff of d in range [l..r)
// thus split i*a to =x (mod d), merge segs. 
void solve() {
    ll n,a,d;
    cin >> n >> a >> d;
    if (d == 0) {
        if (a == 0) {
            cout << 1;
        } else {
            cout << n+1;
        }
        return;
    }

    if (d < 0) {
        a *= -1; d *= -1;
    }

    map<ll, vector<pair<ll,ll>>> mp;
    mp[0].emplace_back(0, 1);
    for (ll i = 1; i <= n; i++) {
        ll s = a*i;
        ll l = i*(i-1)/2;
        ll r = (2*n-i-1)*i/2 + 1;
        ll x = ((s%d)+d)%d; // caution, a could <0
        ll k = (s-x)/d;
        l += k, r += k;
        mp[x].emplace_back(l, r);
    }

    ll res = 0;
    for (auto& _: mp) {
        auto& a = _.second;
        sort(a.begin(), a.end());
        ll l, r;
        tie(l, r) = a[0];
        for (auto& p: a) {
            ll _l, _r;
            tie(_l, _r) = p;
            if (_l > r) {
                res += r - l;
                r = _r;
                l = _l;
            } else {
                r = max(r, _r);
            }
        }
        res += r - l;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
