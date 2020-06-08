#include <bits/stdc++.h>

using namespace std;

// multiset { (xi, xi') } is invariant
void solve() {
    int n; cin >> n;
    vector<int> a(n),b(n);
    for (auto& x: a) cin >> x;
    for (auto& x: b) cin >> x;
    if (n&1 && a[n/2]!=b[n/2]) {
        cout << "No\n"; return;
    }
    map<pair<int,int>,int> cnt;
    for (int i = 0; i < n/2; i++) {
        int x = a[i], y = a[n-i-1];
        cnt[{min(x,y), max(x,y)}]++;
        x = b[i], y = b[n-i-1];
        cnt[{min(x,y), max(x,y)}]--;
    }
    for (auto& c: cnt) {
        if (c.second != 0) {
            cout << "No\n"; return;
        }
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
