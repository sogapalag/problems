#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, s, t;
    cin >> n >> s >> t;
    int x = s+t - n;
    int res = max(s-x, t-x) + 1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    while (q--)solve();
    cout << endl;
}
