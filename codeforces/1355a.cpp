#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// after some turn f(a)=0.
// proof, mi*mx <=81.
// let a=hundred-digit of a. note d(a)<=1., so after 900 turns, a=0.
void solve() {
    ll a,n;
    cin >> a >> n;
    --n;
    auto f = [](ll x){
        string s = to_string(x);
        int mi = 9, mx = 0;
        for (char c:s) {
            mi = min(mi, c-'0');
            mx = max(mx, c-'0');
        }
        return mi*mx;
    };
    while (n > 0 && f(a) > 0) {
        a += f(a); --n;
    }
    cout << a << "\n";
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
