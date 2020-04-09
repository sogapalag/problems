#include <bits/stdc++.h>

using namespace std;

int a[512][512];
// 14 13 12 16 
// 15 2 1 11 
// 5 3 7 9 
// 6 4 8 10
// either rook/queen would exhaust below part, and hit 11
// 14 13 12 16 
// 15       11
//          ^
// then rook will goto 15, then finish remain, 0-trans
// queen will goto 12, finally 15-16 need 1-trans
void solve() {
    int n; cin >> n;
    if (n < 3) {
        cout << -1; return;
    }
    int x = 1;
    for (int j = n-1; j >= 2; j--) {
        a[2][j] = x++;
    }
    for (int i = 3; i <= n; i++) {
        a[i][2] = x++;
    }
    for (int j = 1; j <= n; j++)if(j!=2) {
        for (int i = 3; i <= n; i++) {
            a[i][j] = x++;
        }
    }
    a[2][n] = x++;
    for (int j = n-1; j >= 1; j--) {
        a[1][j] = x++;
    }
    a[2][1] = x++;
    a[1][n] = x++;
    assert(x-1==n*n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j] << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
