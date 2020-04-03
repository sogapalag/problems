#include <bits/stdc++.h>

using namespace std;

// when range [l, r), has property P~notP, want last P.
// when return l-1, means not found.
template <typename T>
T bs_last(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    return r-1;
}

void solve() {
    int n,m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (auto& p: a) {
        cin >> p.first >> p.second;
    }
    vector<int> c(m);
    for (auto& x: c) cin >> x;
    sort(a.begin(), a.end());
    sort(c.begin(), c.end());

    // direct impl use suffix.
    // overkill, a.second is useless actually. and no need bs, just two-pointer greedy is enough.
    auto ck = [&](int k){
        priority_queue<int, vector<int>, greater<int>> hp;
        int i = 0;
        int las = 0;
        for (int _ = m-k; _ < m; _++) {
            int x = c[_];
            while (i < n && a[i].first <= x) {
                int y = a[i++].second;
                if (las <= y) {
                    hp.push(y);
                }
            }
            if (hp.empty()) return false;
            las = hp.top(); hp.pop();
        }
        return true;
    };
    int res = bs_last<int>(0, min(n,m)+1, ck);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
