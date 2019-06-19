#include <bits/stdc++.h>

using namespace std;

using ll=long long;

void solve() {
    int n, k;
    cin >> n >> k;
    int a, b;
    cin >> a >> b;
    int d[4] = {a+b, a-b, -a+b, -a-b};

    ll Z = (ll)n*k;
    vector<ll> dif; dif.reserve(n*10);
    for (int i = -(n-1); i < n; i++) {
        for (int j = 0; j < 4; j++) {
            ll tmp = (ll) i * k  + d[j];
            tmp = abs(tmp) % Z;
            dif.emplace_back(tmp);
        }
    }
    ll x = Z, y = 1;
    for (auto& p: dif) {
        if (!p) x = 1;
        else {
            ll g = __gcd(p, Z);
            g = Z/g;
            x = min(x, g);
            y = max(y, g);
        }
    }
    cout << x << ' ' << y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
