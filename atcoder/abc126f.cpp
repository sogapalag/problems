#include <bits/stdc++.h>

using namespace std;


void solve() {
    int m, k;
    cin >> m >> k;
    if (k >= 1<<m || (k == 1 && m == 1)) {
        cout << "-1";
        return;
    }
    if (k == 0 && m == 1) {
        cout << "0 0 1 1";
        return;
    }
    for (int i = (1<<m)-1; i >= 0; i--) {
        if (i != k) {
            cout << i << ' ';
        }
    }
    cout << k << ' ';
    for (int i = 0; i < 1<<m; i++) {
        if (i != k) {
            cout << i << ' ';
        }
    }
    cout << k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
