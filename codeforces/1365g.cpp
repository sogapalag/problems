#include <bits/stdc++.h>

using namespace std;
using ll=long long;


// a trivial binary method, 2*log n
//   let mask = index, query dp[i][0/1] be OR of all mask with bit i = 0/1
//   thus we can get res[mask] = OR of dp[i][0/1] s.t. i-bit differ from mask
// optimal solution by Sperner's theorem: width of antichain <= C(n, n/2)
//  C(13, 6) = 1716
// thus res[mask] = OR of 0-bits of mask, since incomparable(not sub/super) include all other mask
void solve() {
    int n; cin >> n;
    vector<int> a; // antichain
    for (int i = 0; i < 1<<13; i++) {
        if (__builtin_popcount(i) == 6) {
            a.push_back(i);
        }
    }
    assert((int)a.size() >= n);
    vector<ll> bit(13);
    for (int i = 0; i < 13; i++) {
        vector<int> q;
        for (int j = 0; j < n; j++) {
            if (a[j]>>i&1) q.push_back(j);
        }
        if (!q.empty()) {
            cout << "? " << q.size() << '\n';
            for (int x:q) cout << x+1 << ' ';
            cout << endl;
            cin >> bit[i];
        }
    }
    cout << "! ";
    for (int i = 0; i < n; i++) {
        ll res = 0;
        for (int j = 0; j < 13; j++) {
            if (a[i]>>j&1) continue;
            res |= bit[j];
        }
        cout << res << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
