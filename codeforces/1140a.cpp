#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int cnt = 0;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, a[i]);
        if (i == mx) cnt++;
    }
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
