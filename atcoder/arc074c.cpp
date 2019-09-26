#include <bits/stdc++.h>

using namespace std;
using ll=long long ;
ll cut(ll n, ll i, ll m) {
    ll x = i*m;
    ll res = 1ll<<60;
    if (n-i > 1){
        ll y = (n-i)/2;
        ll z = n-i - y;
        y*=m; z*=m;
        ll d = max({x,y,z}) - min({x,y,z});
        res = min(res, d);
    }
    if (m > 1) {
        ll y = m/2;
        ll z = m - y;
        y*=n-i; z*=n-i;
        ll d = max({x,y,z}) - min({x,y,z});
        res = min(res, d);
    }
    return res;
}

void solve() {
    int n,m;
    cin >> n >> m;
    if (n%3==0 || m%3==0) {
        cout << 0; return;
    }
    ll res = 1ll<<60;
    if (n/3 > 0) res = min(res, cut(n,n/3,m));
    res = min(res, cut(n,n/3+1,m));
    swap(n,m);
    if (n/3 > 0) res = min(res, cut(n,n/3,m));
    res = min(res, cut(n,n/3+1,m));
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
