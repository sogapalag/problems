#include <bits/stdc++.h>

using namespace std;


// slider O(n)
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        b[i] = max(a[i], a[i+n-m]);
    }
    k = min(k, m-1);

    int d = m - k;
    int res = 0;
    for (int i = 0; i+d <= m; i++) {
        int mi = 1e9;
        for (int j = i; j < i+d; j++) {
            mi = min(mi, b[j]);
        }
        res = max(res, mi);
    }
    cout << res << "\n";
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
