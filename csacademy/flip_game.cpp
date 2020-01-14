#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for (auto& x: a) {
        for (int i = 0; i < m; i++) {
            ll bit; cin >> bit;
            x |= bit<<(m-i-1);
        }
    }
    const int MSK = (1ll<<m) - 1; 
    for (auto& x: a) {
        if (x>>(m-1)&1) continue;
        x ^= MSK;
    }
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        int cnt = 0;
        for (auto& x: a) {
            cnt += x>>i&1;
        }
        sum += max(cnt, n-cnt) * (1ll<<i);
    }
    cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
