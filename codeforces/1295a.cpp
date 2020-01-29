#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    if (n&1) {
        n-=3; cout << 7;
    }
    n/=2;
    for (int _ = 0; _ < n; _++) {
        cout << 1;
    }cout << "\n";
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
