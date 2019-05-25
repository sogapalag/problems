#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    int ML=0, mR=1e6;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        ML = max(ML, x);
        mR = min(mR, y);
    }
    int res = ML > mR ? 0: mR-ML+1;
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
