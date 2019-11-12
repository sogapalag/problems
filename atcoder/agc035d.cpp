#include <bits/stdc++.h>

using namespace std;
using ll=long long;
int a[20];

// x,y are coeffs of l-1, r+1, dp is sum [l..r]
ll dp(int l, int r, ll x, ll y) {
    if (l > r) return 0;
    if (l == r) return (x+y) * a[l];
    ll mi = 1ll<<62;
    // if m be last to eat to l-1, r+1. we know a[m]'s coeff
    for (int m = l; m <= r; m++) {
        mi = min(mi, dp(l, m-1, x, x+y) + dp(m+1, r, x+y, y) + (x+y)*a[m]);
    }
    return mi;
}
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << dp(1, n-2, 1, 1) + a[0] + a[n-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
