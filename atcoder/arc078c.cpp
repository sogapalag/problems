#include <bits/stdc++.h>

using namespace std;
using ll=long long ;

void solve() {
    int n; cin >> n;
    vector<ll> sum(n+1);
    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        sum[i] = sum[i-1] + x;
    }
    ll res = 1ll<<60;
    for (int i = 1; i < n; i++) {
        ll d = abs(2*sum[i] - sum[n]);
        res = min(res, d);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
