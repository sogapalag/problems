#include <bits/stdc++.h>

using namespace std;

using ll=long long ;

#define rep(i) for(int i:{1,-1})

void solve() {
    int n,m;
    cin >> n >> m;
    vector<array<ll,3>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    ll res = -1e15;
    rep(x)rep(y)rep(z) {
        vector<ll> b(n);
        for (int i = 0; i < n; i++) {
            b[i] = x*a[i][0] + y*a[i][1] + z*a[i][2];
        }
        sort(b.begin(), b.end(), greater<ll>());
        ll tmp = 0;
        for (int i = 0; i < m; i++) {
            tmp += b[i];
        }
        res = max(res, tmp);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
