#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<long long> s(n);
    for (auto& x: s) {
        cin >> x;
    }
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    int m = s.size();
    vector<long long> d(m+1);
    d[0] = 0;
    d[m] = 1ll<<62;
    for (int i = 1; i < m; i++) {
        d[i] = s[i] - s[i-1];
    }
    sort(d.begin(), d.end());
    vector<long long> sum(m+1);
    sum[0] = 0;
    for (int i = 1; i <= m; i++) {
        sum[i] = sum[i-1] + d[i];
    }
    int q; cin >> q;
    while (q--) {
        long long l, r;
        cin >> l >> r;
        r -= l;
        int i = lower_bound(d.begin(), d.end(), r+1) - d.begin();
        long long res = sum[i-1] + (r+1) * (m-i+1);
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
