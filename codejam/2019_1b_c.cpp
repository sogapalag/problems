#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 18; // 20;
    int k;
    int n;
    vector<int> st[LOG];
    Rmq(vector<T> _v) { // pass in vec[0, n)
        raw = _v;
        n = raw.size();
        k = 32 - __builtin_clz(n);
        for (int j = 0; j < k; j++) {
            st[j].resize(n);
        }
        build();
    }
    inline int comp(int x, int y) { // DO! > max
        return (raw[x] > raw[y] || (raw[x] == raw[y] && x < y)) ? x : y;
    }
    void build() {
        for (int i = 0; i < n; i++) {
            st[0][i] = i;
        }
        for (int j = 1; j < k; j++) {
            for (int i = 0; i + (1<<j) <= n; i++) {
                st[j][i] = comp(st[j-1][i], st[j-1][i + (1<<(j-1))]);
            }
        }
    }
    // [l, r)
    inline int query_id(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return comp(st[j][l], st[j][r - (1<<j)]);
    }
    inline T query(int l, int r) {
        return raw[query_id(l, r)];
    }
};
// when range [l, r), has property notP~P, want first P.
// when return r, means not found.
template <typename T>
T bs_first(T l, T r, function<bool (T)> f) {
    assert(l < r);
    T mid;
    while (l != r) {
        mid = l + (r-l)/2;
        if (f(mid)) {
            r = mid;
        }else {
            l = mid + 1;
        }
    }
    return r;
}
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
using ll=long long;
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n),b(n);
    for (auto& x: a) {
        cin >> x;
    }
    for (auto& x: b) {
        cin >> x;
    }
    Rmq<> ra(a), rb(b);
    ll res = 0;
    function<void(int,int)> divi = [&](int l, int r){
        if (l>=r) return;
        int m = ra.query_id(l, r);
        divi(l,m); divi(m+1,r);
        int L = bs_first<int>(l, m+1, [&](int i){
                return ra.query_id(i, m+1) == m && rb.query(i, m+1) <= a[m] + k;
                });
        int R = bs_last<int>(m, r, [&](int i){
                return ra.query_id(m, i+1) == m && rb.query(m, i+1) <= a[m] + k;
                });
        if (L <= m && m <= R) {
            res += (m-L+1) *1ll* (R-m+1);
        }
        L = bs_first<int>(l, m+1, [&](int i){
                return ra.query_id(i, m+1) == m && rb.query(i, m+1) < a[m] - k;
                });
        R = bs_last<int>(m, r, [&](int i){
                return ra.query_id(m, i+1) == m && rb.query(m, i+1) < a[m] - k;
                });
        if (L <= m && m <= R) {
            res -= (m-L+1) *1ll* (R-m+1);
        }
    };
    divi(0, n);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
    return 0;
}
