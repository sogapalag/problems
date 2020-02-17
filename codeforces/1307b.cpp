#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,d;
    cin >> n >> d;
    int mx = 0;
    bool one = false;
    for (int _ = 0; _ < n; _++) {
        int x; cin >> x;
        if (x == d) {
            one = true;
        }
        mx = max(mx, x);
    }
    // special case
    if (one) {
        cout << "1\n"; return;
    } else if (mx > d) {
        cout << "2\n"; return;
    }
    // since any angle, imagine slightly pickup
    int res = (d+mx-1)/mx;
    cout << res << '\n';
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
