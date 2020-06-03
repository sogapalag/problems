#include <bits/stdc++.h>

using namespace std;
using ll=long long;
const int INF = 1e9; 
// x range small, iter mx.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    ll res = 0;
    for (int mx = 0; mx <= 30; mx++) {
        ll sum = 0;
        ll pref = 0;
        for (int x:a) {
            if (x > mx) x = -INF;
            sum += x;
            pref = min(pref, sum);
            res = max(res, sum-pref - mx);
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
