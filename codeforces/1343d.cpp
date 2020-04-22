#include <bits/stdc++.h>

using namespace std;


// [x+1..k+y] need 1 additional, except x+y. other two
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    vector<int> c(2*k+2);
    for (int i = 0; i < n/2; i++) {
        int x = a[i], y = a[n-i-1];
        if (x > y) swap(x, y);
        c[x+1]++; c[k+y+1]--;
        c[x+y]++; c[x+y+1]--;
    }
    int mx = 0;
    for (int i = 1; i <= 2*k; i++) {
        c[i] += c[i-1];
        mx = max(mx, c[i]);
    }
    cout << n-mx << "\n";
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
