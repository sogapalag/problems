#include <bits/stdc++.h>

using namespace std;
using ll=long long;
int W;
// easy case could ask [1..6], then solve equation.
// hard case is note that r_i<=100, within 7 bits. and for d-day, r_i * 2^(d/i), i.e. shift
//   we query that bit separate, we can distinguish
void solve() {
    // for (int d = 1; d <= 200; d++) {
    //     for (int i = 1; i <= 6; i++) {
    //         cout << (d/i) << ' ';
    //     }cout << '\n';
    // }
    // 50 25 16 12 10 8
    // 200 100 66 50 40 33
    cout << 50 << endl;
    ll x; cin >> x;
    ll r[7];
    r[1] = x>>50;
    r[2] = (x>>25)&127;
    cout << 200 << endl;
    ll y; cin >> y;
    r[4] = (y>>50)&127;
    r[5] = (y>>40)&127;
    r[6] = (y>>33)&127;
    r[3] = x - (r[1]<<50) - (r[2]<<25) - (r[4]<<12) - (r[5]<<10) - (r[6]<<8);
    r[3] >>= 16;
    for (int i = 1; i <= 6; i++) {
        cout << r[i] << ' ';
    }cout << endl;
}

// keep in mind what format needed!! might WA!
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T >> W;
    for (int t = 1; t <= T; t++) {
        solve();
        int verdict; cin >> verdict;
        assert(verdict == 1);
    }
    return 0;
}
