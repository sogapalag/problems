#include <bits/stdc++.h>

using namespace std;
using ll=long long;

// wlog for group l>r.
// recall Hall's, by k-ord, we reserve at most k candidate. obvious optimal
// since lsize + rsize <= n, so two group won't intersect
void solve() {
    int n; cin >> n;
    vector<vector<int>> L(n), R(n);
    ll res = 0;
    for (int _ = 0; _ < n; _++) {
        int k,l,r;
        cin >> k >> l >> r;
        // special
        if (k == n) {
            res += l; continue;
        }
        // l/r better?
        if (l < r) {
            res += l;
            R[n-k].push_back(r-l);
        } else {
            res += r;
            L[k].push_back(l-r);
        }
    }
    {
        priority_queue<int, vector<int>, greater<int>> hp;
        for (int i = 1; i < n; i++) {
            for (int x:L[i]) hp.push(x);
            while (hp.size() > i) {
                hp.pop();
            }
        }
        while (!hp.empty()) {
            res += hp.top(); hp.pop();
        }
    }
    {
        priority_queue<int, vector<int>, greater<int>> hp;
        for (int i = 1; i < n; i++) {
            for (int x:R[i]) hp.push(x);
            while (hp.size() > i) {
                hp.pop();
            }
        }
        while (!hp.empty()) {
            res += hp.top(); hp.pop();
        }
    }
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        solve();
    }
    return 0;
}
