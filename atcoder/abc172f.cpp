#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// a+b = (a^b) + (a&b)<<1
//  => S = C + D<<1
// let a = a'+D = a'^D, same b
//  => a&b = 0, a^b = C, D&C=0
// greedy assign C's higher bits to a
void solve() {
    int n; cin >> n;
    ll A,B,C = 0;
    cin >> A >> B;
    for (int i = 3; i <= n; i++) {
        ll x; cin >> x;
        C ^= x;
    }
    ll S = A + B;
    if (S<C || ((S-C)&1)) {
        cout << -1; return;
    }
    ll D = (S-C)/2;
    if (D&C) {
        cout << -1; return;
    }
    if (D > A) {
        cout << -1; return;
    }
    ll a = 0;
    for (int i = 60; i >= 0; i--) {
        if (C>>i&1) {
            if (a+(1ll<<i)+D <= A) a += 1ll<<i;
        }
    }
    ll res = A-D-a;
    if (res == A) {
        cout << -1; return;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
