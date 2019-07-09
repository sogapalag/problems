#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

ll f(ll l, ll a, ll n, ll d) {
    if (d==1) return l*a;
    if (d==2) {
        ll x = n-1;
        if ((l+x-1)/x > a) return -1;
        ll k = l/x, r = l%x;
        return x*(k*a - k*(k-1)/2) + r*(a-k);
    }
    ll res = -1;
    for (ll x = 1; ;x++) {
        ll fst = n - x*(d-2) - 1;
        if (fst < x) break;
        if ((l-fst+x-1)/x > a-1) continue;
        ll k = (l-fst)/x, r = (l-fst)%x;
        ll tmp = fst*a + x*(k*a - k*(k+1)/2) + r*(a-k-1);
        res = max(res, tmp);
    }
    return res;
}

// fst>=x..=x..
// s.t. fst+x+..+x+1 = n
void solve() {
    int l, a, n, d;
    cin >> l >> a >> n >> d;
    ll res = f(l,a,n,d);
    if (res > 0)
        cout << res << "\n";
    else
        cout << "SAD" << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--)solve();
    cout << endl;
}
