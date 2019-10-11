#include <bits/stdc++.h>

using namespace std;
using ll=long long;

void solve() {
    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> s; s.reserve(n*(n+1)/2);
    for (int i = 0; i < n; i++) {
        ll sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            s.emplace_back(sum);
        }
    }

    ll res = 0;
    const int L = 40;
    for (int j = L; j >= 0; j--) {
        ll k = 1ll<<j;
        ll tar = res|k;
        int cnt = 0;
        for (auto& x: s) {
            if ((x&tar) == tar) cnt++;
        }
        if (cnt >= K) res = tar;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
