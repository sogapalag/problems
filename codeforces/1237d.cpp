#include <bits/stdc++.h>

using namespace std;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 20;
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
        return raw[x] < raw[y] ? x : y;
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

void solve() {
    int n; cin >> n;
    vector<int> a(3*n);
    int mx = -1, mi = 2e9;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mx = max(mx, x);
        mi = min(mi, x);
        a[i] = a[i+n] = a[i+2*n] = x;
    }
    if (mi >= (mx+1)/2) {
        for (int i = 0; i < n; i++) {
            cout << "-1 ";
        }
        return;
    }
    
    Rmq<> R(a);
    vector<int> nxt(3*n); // first j>i. a[j]<a[i]/2
    for (int i = 0; i < 2*n; i++) {
        int half = (a[i]+1)/2;
        nxt[i] = bs_first<int>(i+1, 3*n, [&](int j){
                return R.query(i,j+1) < half;
                });
    }
    for (int i = 2*n; i < 3*n; i++) {
        nxt[i] = 3*n;
    }
    Rmq<> N(nxt);
    for (int i = 0; i < n; i++) {
        int res = bs_first<int>(i+1, 3*n, [&](int j){
                return N.query(i,j) <= j;
                }) - i;
        cout << res << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    cout << endl;
}
