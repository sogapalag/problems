#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// recall Hall's, ensure no continous in-out<0
// which := b_{-1} + sum(b-a), we wanna mini that, recall Kadane's
void solve() {
    int n; cin >> n;
    vector<int> a(2*n), b(2*n);
    ll sa = 0, sb = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i]; a[i+n] = a[i];
        sa += a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i]; b[i+n] = b[i];
        sb += b[i];
    }
    if (sb < sa) {
        cout << "NO\n"; return;
    }
    ll sum = 0, suff = 0;
    // note sb>=sa already ensure len<n
    for (int i = 2*n-1; i >= 1; i--) {
        sum += b[i] - a[i];
        if (b[i-1] + sum-suff < 0) {
            cout << "NO\n"; return;
        }
        suff = max(suff, sum);
    }
    cout << "YES\n";
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
