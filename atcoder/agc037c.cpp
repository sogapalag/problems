#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    vector<int> f(n);
    iota(f.begin(), f.end(), -1); f[0] += n;
    vector<int> g(n);
    iota(g.begin(), g.end(), 1); g[n-1] = 0;
    auto nei = [&](int i){
        return b[f[i]] + b[g[i]];
    };
    auto ok = [&](int i){
        return nei(i) < b[i];
    };
    // not necessary stk, we can operate in any order
    vector<int> stk; stk.reserve(n);
    for (int i = 0; i < n; i++) {
        if (ok(i)) stk.emplace_back(i);
    }
    long long res = 0;
    while (!stk.empty()) {
        int i = stk.back(); stk.pop_back();
        if (!ok(i)) continue;
        if (b[i] < a[i]) {
            cout << -1; return;
        }
        int diff = b[i] - a[i];
        int k = diff / nei(i);
        res += k; b[i] -= k * nei(i);
        if (ok(f[i])) stk.emplace_back(f[i]);
        if (ok(g[i])) stk.emplace_back(g[i]);
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            cout << -1; return;
        }
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
