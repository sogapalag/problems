#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n), c(m);    
    for (auto& x: a) cin >> x;
    for (auto& x: c) cin >> x;
    sort(a.begin(), a.end(), greater<int>());
    vector<int> cnt(m+1);
    for (auto& x: a) {
        cnt[x]++;
    }
    int res = 1;
    for (int i = m-1, s = 0; i >= 0; i--) {
        s += cnt[i+1];
        res = max(res, (s+c[i]-1)/c[i]);
    }
    vector<vector<int>> g(res);
    // key form
    for (int i = 0; i < n; i++) {
        g[i%res].push_back(a[i]);
    }
    cout << res << "\n";
    for (auto& b: g) {
        cout << b.size() << ' ';
        for (auto& x: b) {
            cout << x << ' ';
        }cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
