#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int k,q;
    cin >> k >> q;
    vector<ll> d(k);
    for (auto& x: d) {
        cin >> x;
    }
    while (q--) {
        ll n,x,m;
        cin >> n >> x >> m;
        n--;
        x %= m;
        ll sum = 0;
        for (auto& x: d) {
            sum += x%m;
        }
        // a_n
        ll z = x + (n/k) * sum;
        {
            ll r = n%k;
            for (int i = 0; i < r; i++) {
                z += d[i]%m;
            }
        }
        
        // #>, cross
        ll res = z / m;
        // #=,
        for (int i = 0; i < k; i++) {
            if (d[i]%m == 0 && i < n) {
                res += 1 + (n-i-1) / k;
            }
        }
        res = n - res;
        cout << res << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
