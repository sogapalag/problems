#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    ll n,k;
    cin >> n >> k;
    ll res;
    if (k&1) {
        ll x=n/k;
        res = x*x*x;
    } else {
        ll x=n/k;
        res =x*x*x;
        x = n/(k/2) - n/k;
        res +=x*x*x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
