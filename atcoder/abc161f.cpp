#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// n = d^e(id+1)
void solve() {
    ll n;cin >> n;
    // e > 0
    int res = 1;
    for (ll d = 2; d*d <= n; d++) {
        if (n % d == 0) {
            ll x = n;
            while (x % d == 0) {
                x /= d;
            }
            if (x % d == 1) res++;
        }
    }
    // e = 0
    res += (n>2);
    for (ll d = 2; d*d <= n-1; d++) {
        if ((n-1) % d == 0) {
            res++;
            if (d*d != n-1)res++;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
