#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    int R = 2e9, L = 0, D = 0;
    for (int i = 0; i < n; i++) {
        int l,r;
        cin >> l >> r;
        r++;
        R = min(R, r);
        L = max(L, l);
        D = max(D, r - l);
        a[i] = {l, r};
    }
    int res = D + max(0, R - L);
    for (auto& p: a) {
        p.first = max(0, R - p.first);
        p.second = max(0, p.second - L);
    }
    sort(a.begin(), a.end(), [&](auto& u, auto& v){
            return u.first < v.first || (u.first == v.first && u.second > v.second);
            });
    int mi = a[0].second;
    for (int i = 1; i < n; i++) {
        res = max(res, mi + a[i].first);
        mi = min(mi, a[i].second);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
