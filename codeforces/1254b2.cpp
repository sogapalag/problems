#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// next time not 100% sure whether natural method work, but do give a summit try.
void solve() {
    int n; cin >> n;
    ll k = 0;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
        k += x;
    }
    if (k==1){
        cout << -1; return;
    }
    // only ps, not ds, since p|d always better
    vector<ll> ps;
    for (ll d = 2; d*d <= k; d++) {
        if (k % d == 0) {
            ps.emplace_back(d);
            while (k % d == 0) {
                k /= d;
            }
        }
    }
    if (k!=1) ps.emplace_back(k);
    
    // flow on sides, don't focus on i, but on region. this lower_bound always achieve
    ll res = 1ll<<62;
    for (ll p: ps) {
        ll sum = 0;
        ll flow = 0;
        for (int x: a) {
            sum += x;
            ll rem = sum % p;
            flow += min(rem, p-rem);
        }
        res = min(res, flow);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
