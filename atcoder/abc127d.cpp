#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector<pair<int, int>> cb(m);
    for (auto& p: cb) {
        cin >> p.second >> p.first;
    }
    sort(cb.begin(), cb.end(), [&](auto& u, auto& v){
            return u.first > v.first;
            });
    long long res = 0;
    auto it = a.begin();
    for (auto& p: cb) {
        int c = p.first, b = p.second;
        auto jt = lower_bound(it, a.end(), c);
        int k = jt - it;
        int d = min(k, b);
        res += 1ll*d*c;
        it += d;
        if (d < b || it == a.end()) {
            break;
        }
    }
    for (; it != a.end(); it++) {
        res += *it;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
