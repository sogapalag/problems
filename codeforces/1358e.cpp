#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// k valid => 2k valid
// => if valid exist valid len > n/2
// thus, sum's shifts can be pre-calced
void solve() {
    int n; cin >> n;
    int m = (n+1)/2;
    vector<int> a(n);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    int X; cin >> X;
    for (int i = m; i < n; i++) {
        a[i] = X;
    }
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    // shifts
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = X - a[i];
    }
    for (int i = 1; i < n; i++) {
        b[i] += b[i-1];
    }
    // pref min
    for (int i = 1; i < n; i++) {
        b[i] = min(b[i], b[i-1]);
    }

    for (int k = m; k <= n; k++) {
        if (sum[k] > 0) {
            if (k==n || sum[k] + b[n-k-1] > 0) {
                cout << k; return;
            }
        }
    }
    cout << -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
