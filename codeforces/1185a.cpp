#include <bits/stdc++.h>

using namespace std;


void solve() {
    int a[3], d;
    cin >> a[0] >> a[1] >> a[2];
    cin >> d;
    sort(a, a+3);
    int res = max(0, d - (a[2]-a[1]));
    res += max(0, d - (a[1] - a[0]));
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
