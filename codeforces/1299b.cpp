#include <bits/stdc++.h>

using namespace std;


// no idea in time, just try central symmetry.
// check editorial proof. omit.
void solve() {
    int n; cin >> n;
    if (n&1) cout << "NO";
    else {
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            int x,y;
            cin >> x >> y;
            a[i] = {x,y};
        }
        int m = n/2;
        for (int i = 0; i < m; i++) {
            int dx = a[i+1].first - a[i].first;
            int dy = a[i+1].second - a[i].second;
            int du = a[(i+m+1)%n].first - a[i+m].first;
            int dv = a[(i+m+1)%n].second - a[i+m].second;
            if (dx+du!=0 || dy+dv!=0) {
                cout << "NO"; return;
            }
        }
        cout << "YES";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
