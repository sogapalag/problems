#include <bits/stdc++.h>

using namespace std;
using ll=long long;

ll a[3][4] = {
    {0, 1, 2, 3},
    {0, 2, 3, 1},
    {0, 3, 1, 2}};

// write brute-force find pattern,
// 3
// 2   a   
// 1  
// each 2bit is a pattern
// the row is like
// 1
// 4= 2^2
// ..
// 7
// 16 = 2^4
// ..
// 31
// 64
// ..
void solve() {
    ll n; cin >> n;
    n--;
    ll r = n / 3 + 1;
    ll c = n%3;
    ll x = 1;
    while (x < r) {
        r -= x;
        x *= 4;
    }
    r--;
    ll p = x * (c+1);
    for (int i = 0; i < 62; i+=2) {
        p |= (a[c][r>>i&3]<<i);
    }
    cout << p << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
