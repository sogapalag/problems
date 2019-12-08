#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,q;
    cin >> n >> q;
    vector<int> r,c; // cut
    int las = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x&=1;
        if (x != las) r.emplace_back(i);
        las = x;
    }r.emplace_back(n);
    las = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; x&=1;
        if (x != las) c.emplace_back(i);
        las = x;
    }c.emplace_back(n);

    while (q--) {
        int x,y,u,v;
        cin >> x >> y >> u >> v;
        // in same rect-region
        if (lower_bound(r.begin(), r.end(), x) == lower_bound(r.begin(), r.end(), u)
                && lower_bound(c.begin(), c.end(), y) == lower_bound(c.begin(), c.end(), v)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
