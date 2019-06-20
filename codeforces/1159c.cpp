#include <bits/stdc++.h>

using namespace std;


// row decide the base
// col add on max base
void solve() {
    int n, m;
    cin >> n >> m;
    int mx0=-1, mx1=-1;
    long long row=0, col=0;
    for (int i = 0; i < n; i++) {
        int b; cin >> b;
        row += b;
        if (b > mx1) {
            mx1 = b;
        }
        if (mx1 > mx0) {
            swap(mx1, mx0);
        }
    }
    int mi = 1e9;
    for (int i = 0; i < m; i++) {
        int g; cin >> g;
        col += g;
        if (g < mi) {
            mi = g;
        }
    }
    if (mx0 > mi) {
        cout << -1; return;
    }
    if (mx0 == mi) {
        long long res = row*m + col - 1ll*mx0*m;
        cout << res; return;
    }else {
        long long res = row*m + col - 1ll*mx0*(m-1) - mx1;
        cout << res; return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
