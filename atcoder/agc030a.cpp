#include <bits/stdc++.h>

using namespace std;


void solve() {
    int x,y,z;
    cin >> x >> y >> z;
    int res = min(x+y+1, z) + y;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
