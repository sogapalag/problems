#include <bits/stdc++.h>

using namespace std;
using ll=long long;

template <typename T=int>
struct Rmq {
    vector<T> raw;
    static const int LOG = 19; // 20;
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
        return raw[x] > raw[y] ? x : y;
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
void solve() {
    int n, A;
    cin >> n >> A;
    vector<int> a(n), c(n);
    ll res = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> c[i];
        c[i] = A - c[i];
        res = max(res, (ll)c[i]);
    }
    
    if (n > 1) {
        vector<int> d(n-1);
        for (int i = 1; i < n; i++) {
            d[i-1] = a[i] - a[i-1];
        }
        vector<ll> X(n+1), Y(n+1);
        for (int i = 0; i < n; i++) {
            X[i+1] = X[i] + c[i];
        }
        for (int i = n-1; i >= 0; i--) {
            Y[i] = Y[i+1] + c[i];
        }
        Rmq<ll> rx(X), ry(Y);
        Rmq<int> rd(d);
        // divi gap pos. careful +1+1..
        function<void(int,int)> divi = [&](int l, int r){
            if(l>=r) return;
            int m = rd.query_id(l, r);
            //cerr<<l<<' '<<m<<' '<<r<<endl;
            ll gap = d[m]*1ll*d[m];
            ll L = ry.query(l, m+1) - Y[m+1];
            ll R = rx.query(m+1+1, r+1+1) - X[m+1];
            res = max(res, L+R - gap);
            divi(l, m);
            divi(m+1, r);
        };
        divi(0, n-1);
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
