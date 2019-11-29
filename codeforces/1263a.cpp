#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a+3);
    if (a[2] >= a[0]+a[1]) {
        cout << (a[0]+a[1]) << '\n'; return;
    }
    int x = a[2]-a[1];
    int res = a[1] + x;
    a[0] -= x;
    if (a[0]&1) a[0]--;
    a[0]/=2;
    res += min(a[0], a[1]);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
