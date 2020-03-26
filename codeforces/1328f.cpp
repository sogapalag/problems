#include <bits/stdc++.h>

using namespace std;
using ll=long long;


void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    for (int i = k-1; i < n; i++) {
        if (a[i] == a[i-k+1]) {
            cout << 0; return;
        }
    }
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    ll res = 1e18;
    for (int i = 0; i < n; i++)if(!i||a[i]!=a[i-1]) {
        int j = upper_bound(a.begin(), a.end(), a[i]) - a.begin();
        ll x = -sum[i] + i*1ll*(a[i] - 1);
        ll y = sum[n]-sum[j] - (n-j)*1ll*(a[i]+1);
        // use both
        res = min(res, x+y + k-(j-i));
        // left is enough
        if (j >= k) res = min(res, x + k-(j-i));
        // right is enough
        if (n-i >= k) res = min(res, y + k-(j-i));
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
