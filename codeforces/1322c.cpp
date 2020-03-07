#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// key, for each right, its token is which lefts connect to it.
//   those imply they're same group, always occur simult. and there's way their sum contribute.(hard part)
// a intuition way to think, (x+y, y+z), x, z contribute easy to see, since they can be view sum+x
//   y contribute too, sum-x. i.e. one can treat as bit XOR, above group as basis.
void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> left(n, 0);
    vector<vector<int>> right(n);
    for (int _ = 0; _ < m; _++) {
        int x,y;
        cin >> x >> y;
        x--;y--;
        left[x] += a[y];
        right[y].push_back(x);
    }
    ll g = 0;
    for (ll x: left) if(x) g = __gcd(g, x);
    map<vector<int>, ll> mp;
    for (int i = 0; i < n; i++) {
        sort(right[i].begin(), right[i].end());
        if (!right[i].empty()) {
            mp[right[i]] += a[i];
        }
    }
    for (auto& _: mp) {
        ll x = _.second;
        g = __gcd(g, x);
    }
    cout << g << '\n';
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
