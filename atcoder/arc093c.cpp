#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+2);
    a[0] = a[n+1] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n+2), suf(n+2);
    pre[0] = 0;
    for (int i = 1; i <= n+1; i++) {
        pre[i] = pre[i-1] + abs(a[i]-a[i-1]);
    }
    suf[n+1] = 0;
    for (int i = n; i >= 0; i--) {
        suf[i] = suf[i+1] + abs(a[i]-a[i+1]);
    }
    for (int i = 1; i <= n; i++) {
        int res = pre[i-1] + suf[i+1] + abs(a[i-1]-a[i+1]);
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
