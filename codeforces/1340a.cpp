#include <bits/stdc++.h>

using namespace std;


// form [678][45][123]
void solve() {
    int n; cin >> n;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; --a[i];
        p[a[i]] = i;
    }
    int l = p[0], r = n, s = 0;
    while (true) {
        for (int i = l; i < r; i++) {
            if (a[i] != s+i-l) {
                cout << "No\n"; return;
            }
        }
        s += r-l;
        if (s == n) break;
        r = l;
        l = p[s];
    }
    cout << "Yes\n";
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
