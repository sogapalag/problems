#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    vector<ll> sz(n);
    for (auto& x: sz) {
        cin >> x;
    }
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        cin >> p[i]; --p[i];
    }
    for (int i = n-1; i >= 1; i--) {
        sz[p[i]] += sz[i];
    }
    vector<ll> f(n+1);
    for (int i = 0; i < n; i++) {
        ll k = sz[0] / __gcd(sz[0], sz[i]); // at least component
        if (k <= n) f[k]++;
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i*2; j <= n; j+=i) {
            f[j] += f[i];
        }
    }
    // now, f[k]: #could cut with 0=mod(S/k)
    vector<ll> way(n+1);//k region is last-level
    ll res = 0;
    way[1] = 1;
    for (int k = 1; k <= n; k++) {
        if (f[k]==k) {
            res += way[k];
            // #next level is multiple of #prev
            for (int j = k*2; j <= n; j+=k) {
                way[j] += way[k];
            }
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
