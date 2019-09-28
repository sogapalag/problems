#include <bits/stdc++.h>

using namespace std;

using ll=long long;
int n; 
ll f(vector<ll>& a) {
    ll sum = a[0];
    assert(sum != 0);
    ll cost = 0;
    for (int i = 1; i < n; i++) {
        if (sum > 0) {
            sum += a[i];
            ll d = max(sum, -1ll) - (-1);
            sum -= d;
            cost += d;
        } else {
            sum += a[i];
            ll d = 1 - min(sum, 1ll);
            sum += d;
            cost += d;
        }
    }
    return cost;
}

void solve() {
    cin >> n;
    vector<ll> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    ll res = 1ll<<60;
    if (a[0] > 0) {
        res = min(res, f(a));
        ll d = a[0] + 1;
        a[0] = -1;
        res = min(res, d+f(a));
    } else if (a[0] == 0) {
        a[0] = 1;
        res = min(res, 1+f(a));
        a[0] = -1;
        res = min(res, 1+f(a));
    } else {
        res = min(res, f(a));
        ll d = 1 - a[0];
        a[0] = 1;
        res = min(res, d+f(a));
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
