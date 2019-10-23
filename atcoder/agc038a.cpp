#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m, a,b;
    cin >> n >> m >> b >> a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ( (i < a && j < b) || (a<=i && b<=j) ) {
                cout << 0;
            }else cout << 1;
        }cout << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
