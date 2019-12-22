#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    ll n; cin >> n;
    if (n&1){
        cout << 0;return;
    }

    n/=2;
    ll x = 5;
    ll res = 0;
    while (x <= n) {
        res += n/x;
        x *= 5;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
