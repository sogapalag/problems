#include <bits/stdc++.h>

using namespace std;


void solve() {
    int c,m,x;
    cin >> c >> m >> x;
    int most = min(c,m);
    int att = c-most + m-most + x;
    int res = min(most, att);
    if (most > att) {
        res += (most-att)*2/3;
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
