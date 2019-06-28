#include <bits/stdc++.h>

using namespace std;


// b's   01, 10 may cause parity change.
void solve() {
    string a, b;
    cin >> a;
    cin >> b;
    int n = a.size(), m = b.size();
    int cnt = 0;
    for (int i = 1; i < m; i++) {
        if (b[i] != b[i-1]) cnt++;
    }
    cnt &= 1;
    int res = 0;
    int crt = 0;
    for (int i = 0; i < m; i++) {
        if (a[i] != b[i]) crt++;
    }
    crt &= 1;
    res += crt?0:1;
    for (int i = 0; i+m < n; i++) {
        // key part
        crt = (crt - (a[i]!=b[0])) + cnt + (a[i+m] != b[m-1]);
        crt &= 1;
        res += crt?0:1;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
