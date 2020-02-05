#include <bits/stdc++.h>

using namespace std;

// slider of [l,r) r-l=d range min/max
// in begin/end, r-l could < d
template <typename T=int>
struct Slider {
    vector<T> a;
    int n, d;
    deque<int> mi, mx;

    vector<int> lid, hid;

    Slider(vector<T> _a, int _d) : a(_a), d(_d) {
        n = a.size();
        lid.resize(n + d);
        hid.resize(n + d);
        build();
    }
    void build() {
        for (int i = 0; i < n+d-1; i++) {
            while (i < n && !mi.empty() && a[mi.back()] >= a[i]) {
                mi.pop_back();
            }
            mi.push_back(i);
            lid[i+1] = mi.front();
            if (i-d+1 >= 0 && i-d+1 == mi.front()) {
                mi.pop_front();
            }

            while (i < n && !mx.empty() && a[mx.back()] <= a[i]) {
                mx.pop_back();
            }
            mx.push_back(i);
            hid[i+1] = mx.front();
            if (i-d+1 >= 0 && i-d+1 == mx.front()) {
                mx.pop_front();
            }
        }
    }
    
    // [l, r)
    int min_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? lid[r] : lid[l+d];
    }
    T get_min(int l, int r) {
        return a[min_id(l,r)];
    }
    int max_id(int l, int r) {
        assert(1 <= r-l && r-l <= d);
        if (r-l < d) assert(l == 0 || r == n);
        return r < n ? hid[r] : hid[l+d];
    }
    T get_max(int l, int r) {
        return a[max_id(l,r)];
    }
};
using ll=long long;
void solve() {
    int n, lim, m;
    cin >> n >> lim >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> dp(n+1, -1e18);
    dp[0] = 0;
    // by first iter j's order, we don't reimpl a extending version slider. much elegant
    // just use the lib slider, space now O(n) instead O(n^2)
    for (int j = 1; j <= m; j++) {
        Slider<ll> s(dp, lim);
        dp[0] = -1e18;
        for (int i = 1; i <= n; i++) {
            dp[i] = s.get_max(max(i-lim, 0), i) + a[i-1];
        }
    }
    ll res = -1;
    for (int i = n-lim+1; i <= n; i++) {
        res = max(res, dp[i]);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
