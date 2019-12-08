#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n; cin >> n;
    ll res = 0;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        if (x < y) swap(x,y); // >< both work
        res = max(res, (ll)x*y);
        a[i] = {x,y};
    }
    sort(a.begin(), a.end());
    int mx = a[n-1].second;
    for (int i = n-2; i >= 0; i--) {
        res = max(res, 2ll*min(a[i].second, mx) * a[i].first);
        mx = max(mx, a[i].second);
    }
    cout << fixed << setprecision(1) << ((long double)res)/2.0; // double WA
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
