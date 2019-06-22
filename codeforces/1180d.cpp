#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    int i=1, j=n;
    while (i < j) {
        for (int k = 1; k <= m; k++) {
            cout << i << ' ' << k << "\n";
            cout << j << ' ' << (m+1-k) << "\n";
        }
        i++; j--;
    }
    if (i == j) {
        int k = 1, kk = m;
        while (k < kk) {
            cout << i << ' ' << k << "\n";
            cout << i << ' ' << kk << "\n";
            k++; kk--;
        }
        if (k == kk)
            cout << i << ' ' << k << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
