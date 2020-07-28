#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    int cnt = 0;
    int mx = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > mx && (i==n-1 || a[i] > a[i+1])) ++cnt;
        mx = max(mx, a[i]);
    }
    cout << cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
