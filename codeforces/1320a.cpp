#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// take all x-i same
void solve() {
    int n; cin >> n;
    map<int, ll> mp;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int t = x-i;
        mp[t] += x;
    }
    ll res = 0;
    for (auto& _: mp) {
        res = max(res, _.second);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
