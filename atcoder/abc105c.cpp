#include <bits/stdc++.h>

using namespace std;

using ll=long long ;
void solve() {
    ll n; cin >> n;
    ll res = 0;
    int i = 0;
    while (n) {
        ll k = 1ll<<i;
        if (n & k) {
            res |= k;
            n += (i&1)?k:-k;
        }
        i++;
    }
    if (res == 0) {
        cout << 0;
        return;
    }
    //cout << res << "\n";
    int h = 63-__builtin_clzll(res);
    for (int i = h; i >= 0; i--) {
        int x = (res & (1ll<<i))? 1:0;
        cout << x;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
