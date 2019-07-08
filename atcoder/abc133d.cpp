#include <bits/stdc++.h>

using namespace std;

using ll=long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> res(n);
    res[0] = 0;
    for (int i = 1; i < n; i++) {
        res[i] = (ll)a[i-1] - res[i-1];
    }
    ll d = (ll)a[n-1] - res[0] - res[n-1];
    assert((d&1)==0);
    ll h = d/2;
    for (int i = 0; i < n; i++) {
        if (i&1) res[i] -= h;
        else res[i] += h;
    }
    for (auto& x: res) {
        cout << 2*x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
