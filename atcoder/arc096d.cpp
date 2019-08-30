#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

void solve() {
    int n; ll C;
    cin >> n >> C;
    vector<ll> d(n), v(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> v[i];
    }
    auto rd = d;
    vector<ll> L(n),R(n),lx(n),rx(n); // profit, pref-max profit
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i];
        R[i] = sum - rd[i];
        rx[i] = mx = max(mx, R[i]);
    }
    auto ld = d;
    for (auto& x: ld) {
        x = C-x;
    }
    sum = 0, mx = 0;
    for (int i = n-1; i >= 0; i--) {
        sum += v[i];
        L[i] = sum - ld[i];
        lx[i] = mx = max(mx, L[i]);
    }
    ll res = max(lx[0], rx[n-1]); // one-way
    // zig
    for (int i = 0; i < n-1; i++) {
        ll tmp = R[i] - rd[i];
        tmp += lx[i+1];
        res = max(res, tmp);

        tmp = L[i+1] - ld[i+1];
        tmp += rx[i];
        res = max(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
