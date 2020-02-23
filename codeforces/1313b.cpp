#include <bits/stdc++.h>

using namespace std;


// two match performance
// similar problem arc094d
void solve() {
    int n,x,y;
    cin >> n >> x >> y;
    if (x > y) swap(x,y);
    {
        // max some {p} +{c} > x+y
        int p = x-1;
        int c = max(0, n-y-1);
        p -= min(p,c);
        // y+1 can used for x+1
        if (x < n && y == n) p++;
        cout << p+1 << ' ';
    }
    {
        // max some {p}+{c} <= x+y
        int p = n-y;
        int c = x-1;
        p = min(p, c);
        cout << p + y << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
