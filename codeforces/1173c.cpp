#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    vector<int> b(n+1);
    vector<int> p(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]] = 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        p[b[i]] = i;
    }
    // check direct put k,...n
    if (b[n]) {
        bool f = true;
        for (int i = n; i >= n-b[n]+2; i--) {
            if (b[i] != b[i-1] + 1) {
                f = false; break;
            }
        }
        if (f) {
        for (int i = b[n]+1; i <= n; i++) {
            if (p[i] >= i-b[n]) {
                f = false; break;
            }
        } }
        if (f) {
            cout << (n-b[n]); return;
        }
    }
    // each k aval? 000,1..k, k
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, p[i]-i+n+1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
