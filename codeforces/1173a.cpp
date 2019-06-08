#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y,z;
    cin >> x >> y >> z;
    int p = 0, n = 0, e = 0;
    if (x+z > y) p |= 1;
    if (y+z > x) n |= 1;
    if (abs(x-y) <= z) e |= 1;
    
    if (p+n+e > 1) {
        cout << "?"; return;
    }
    assert(p+n+e == 1);
    if (p) cout << "+";
    if (n) cout << "-";
    if (e) cout << "0";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
