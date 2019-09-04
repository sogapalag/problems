#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

void solve() {
    ll a,b;
    cin >> a >> b;
    if (a>b) swap(a,b);
    ll res;
    if (a==b) {
        res = (a-1)*2;
    } else if (a+1==b) {
        res = (a-1)*2;
    } else {
        ll c = floor(sqrt(a*b));
        if (c*c==a*b)c--;
        if (c*(c+1) >= a*b) res=2*c-2;
        else res = 2*c-1;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--) solve();
    cout << endl;
}
