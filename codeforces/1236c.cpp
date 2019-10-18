#include <bits/stdc++.h>

using namespace std;

int a[333][333];

void solve() {
    int n; cin >> n;
    int l = 1, r = n*n;
    int m = n/2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j]=l++;
        }
        for (int j = m+(n&1); j < n; j++) {
            a[i][j]=r--;
        }
    }
    if (n&1) {
        for (int i = 0; i < n; i++) {
            a[i][m]=l++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
