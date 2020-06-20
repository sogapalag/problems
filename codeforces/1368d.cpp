#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// we can always skew bits
void solve() {
    int n; cin >> n;
    vector<int> a(20);
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        for (int i = 0; i < 20; i++) {
            if (x>>i&1) ++a[i];
        }
    }
    ll res = 0;
    for (int _ = 0; _ < n; _++) {
        ll x = 0;
        for (int i = 0; i < 20; i++) {
            if (a[i] > 0) {
                --a[i];
                x += 1<<i;
            }
        }
        res += x*x;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
