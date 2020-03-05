#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n ; cin >> n;
    string s; cin >> s;
    int k = n;
    auto r = s; reverse(r.begin(), r.end());
    for (int i = n-1; i >= 1; i--) {
        string e = s.substr(0, i-1);
        if ((n-i+1) & 1) {
            reverse(e.begin(), e.end());
        }
        string t = s.substr(i-1, n-i+1) + e; // final pattern
        if (t <= r) {
            r = t;
            k = i;
        }
    }
    cout << r << "\n";
    cout << k << '\n';
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
