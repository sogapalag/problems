#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> g[2];
    for (int i = 0; i < n; i++) {
        g[i&1].push_back(a[i]);
    }
    // parity indep, each sorted
    sort(g[0].begin(), g[0].end());
    sort(g[1].begin(), g[1].end());
    for (int i = 0; i < n; i++) {
        a[i] = g[i&1][i/2];
    }
    int i = 0;
    for (;i<n-1;i++) {
        if (a[i] > a[i+1]) break;
    }
    if (i==n-1) {
        cout << "OK\n";
    } else {
        cout << i << '\n';
    }
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
