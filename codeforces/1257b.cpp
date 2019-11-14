#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y;
    cin >> x >> y;
    if (x >= y) {
        cout << "YES\n"; return;
    }
    if (x == 2 && y == 3) {
        cout << "YES\n"; return;
    }
    if (x <= 3) {
        cout << "NO\n"; return;
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
