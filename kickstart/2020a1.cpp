#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,S;
    cin >> n >> S;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= S) {
            res++;
            S -= a[i];
        }
    }
    cout << res << "\n";
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
