#include <bits/stdc++.h>

using namespace std;


//  1 2 3
// 4
// 5  i*j
// 6
void solve() {
    int n,m;
    cin >> n >> m;
    if (n==1&&m==1){
        cout << 0; return;
    }
    if (n<m) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << i*(j+n) << ' ';
            }cout << '\n';
        }
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << (i+m) * j << ' ';
            }cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
