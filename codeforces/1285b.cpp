#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// overkill, another method, note that implies NO if a prefix/suffix sum <= 0.
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    ll A = 0;
    for (auto& x: a) {
        cin >> x;
        A += x;
    }
    ll mi = 0;
    ll sum = 0;
    ll mx = -1e15;
    for (int i = 0; i < n-1; i++) {
        sum += a[i];
        mx = max(mx, sum - mi);
        mi = min(mi, sum);
    }
    sum = 0;
    for (int i = n-1; i >= 1; i--) {
        sum += a[i];
        mx = max(mx, sum);
    }
    cout << (mx<A?"YES\n":"NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--)solve();
    cout << endl;
}
