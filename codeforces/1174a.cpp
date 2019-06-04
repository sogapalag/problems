#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(2*n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        x += a[i];
        y += a[n+i];
    }
    if (x==y) {
        cout << -1;
    } else {
        for (auto& x: a) {
            cout << x << ' ';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
