#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    int mx = -1e9;
    int d = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        d = max(d, mx - x);
        mx = max(mx, x);
    }
    // iff d can reach
    int res = d ? 32-__builtin_clz(d) : 0;
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
