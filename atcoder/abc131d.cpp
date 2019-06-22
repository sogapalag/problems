#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = {y, x};
    }
    sort(a.begin(), a.end());
    int t = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        tie(y, x) = a[i];
        t += x;
        if (t > y) {
            cout << "No"; return;
        }
    }
    cout << "Yes";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
