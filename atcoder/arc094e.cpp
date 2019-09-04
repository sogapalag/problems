#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

// min_{x>y} y. as A doesn't change it until last. achieve sum-y
// for B, strtegy is decrease y for any (x<y)
//   note in the end, some x_i dec to y_i. since B doen't do anything to y_i. among (x>y) y* is minimum, so at most
//   aka y_i in (x>y) >= y*
void solve() {
    int n; cin >> n;
    ll sum = 0; int mi = 2e9;
    bool eq = true;
    for (int _ = 0; _ < n; _++) {
        int x,y;
        cin >> x >> y;
        sum += x;
        if (x > y)
            mi = min(mi, y);
        eq &= x==y;
    }
    if (eq) cout << 0;
    else {
        cout << (sum-mi);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
