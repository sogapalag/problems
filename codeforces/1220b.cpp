#include <bits/stdc++.h>

using namespace std;

int a[1024][1024];

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    int g = 0;
    for (int j = 1; j < n; j++) {
        g = __gcd(g, a[0][j]);
    }
    int x1 = a[0][1]/g, x2=a[0][2]/g;
    int k = sqrt ( (double)a[1][2]/x1/x2 );
    int x0 = g/k;
    cout << x0 << ' ';
    for (int i = 1; i < n; i++) {
        int xi = a[0][i]/x0;
        cout << xi << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
