#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n; cin >> n;
    vector<ll> a;
    ll x = n;
    for (ll i = 2; i*i <= x; i++) {
        if (x%i==0){
            ll d = 1;
            while (x%i==0) {
                x/=i;
                d*=i;
            }
            a.push_back(d);
        }
    }
    if (x!=1)a.push_back(x);

    int m = a.size();
    if (m == 0) {
        cout << "1 1"; return;
    }
    const int MSK = 1<<m; 
    ll mi = n;
    // guess what, no need that pattern, just all d|x, minmax(d,x/d), since covered
    for (int msk = 0; msk < MSK; msk++) {
        ll x = 1;
        for (int i = 0; i < m; i++) {
            if(msk>>i&1)x*=a[i];
        }
        mi = min(mi, max(x, n/x));
    }
    cout << mi << ' ' << (n/mi);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
