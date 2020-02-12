#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// key: for optim, a seg's boarder must its min/max
//  so just maintain prefmax of (dp + x), (dp - x), i.e. dp means cut at here, x as after-boarder
void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll dps = a[0];
    ll dpt = -a[0];

    for (int i = 1; i <= n; i++) {
        int endx = a[i-1], x = a[i];
        ll mx = max(dps - endx, dpt + endx);
        dps = max(dps, mx + x);
        dpt = max(dpt, mx - x);
        if (i == n) cout << mx;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
