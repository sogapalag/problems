#include <bits/stdc++.h>

using namespace std;


// i+x == i'+x, if i'=i (%n)
// so as long as [n]+x <-> [n]
void solve() {
    int n; cin >> n;
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x += i;
        x %= n;
        if (x < 0) x += n;
        cnt[x]++;
    }
    for (int i = 0; i < n; i++) {
        if (cnt[i]!=1) {
            cout << "NO\n"; return;
        }
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
