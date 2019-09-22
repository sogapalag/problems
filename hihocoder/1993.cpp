#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n+1), b(n+1);
    a[0] = 0; b[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    int i = upper_bound(a.begin(), a.end(), c) - a.begin();
    i--;
    if (i == n) {
        cout << b[n];
    } else {
        cout << b[i] << ' ' << (a[i+1]-c) << ' ' << b[i+1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
