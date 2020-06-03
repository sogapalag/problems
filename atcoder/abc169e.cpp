#include <bits/stdc++.h>

using namespace std;

// continous 1 (odd), 1/2 (even)
// and LB/UB happen when all a/b
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int m = n/2;
    int res = (n&1) ? b[m]-a[m]+1 : (b[m-1]+b[m]) - (a[m-1]+a[m]) +1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
