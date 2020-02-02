#include <bits/stdc++.h>

using namespace std;

template <typename M>
struct SegTree {
    using Op = function<M(const M&, const M&)>;
    M ID; // monoid identity
    Op op; // associative operation
    int N; // 2^lg space, for non-commutative
    vector<M> a;
    
    SegTree(int n, M leaf_default, M _ID, Op _op) : ID(_ID), op(_op) {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegTree(const vector<M> leaves, M _ID, Op _op) : ID(_ID), op(_op) {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; while (N < n) N<<=1;
        a.assign(N<<1, ID);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }

    void assign(int p, M val) {
        assert(0 <= p && p < N);
        for (a[p += N] = val; p >>= 1;) pull(p);
    }
    void better(int p, M val) {
        assert(0 <= p && p < N);
        p += N;
        for (a[p] = op(a[p], val); p >>= 1;) pull(p);
    }
    M query(int l, int r) const {
        assert(0 <= l && r <= N);
        M resl(ID), resr(ID);
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = op(resl, a[l++]);
            if (r & 1) resr = op(a[--r], resr);
        }
        return op(resl, resr);
    }
    M query_point(int p) const { 
        assert(0 <= p && p < N);
        return a[p + N];
    }
    M query_all() const { return a[1]; }
};
using ll=long long;
void solve() {
    int n,q,A,B;
    cin >> n >> q >> A >> B;
    vector<int> a(q+1);
    a[0] = A;
    for (int i = 1; i <= q; i++) {
        cin >> a[i];
    }

    SegTree<ll> s (n+3, 1e18, 1e18,
            [](ll u, ll v){ return min(u,v); }
            );
    auto t = s;

    s.assign(B, -B);
    t.assign(B, +B);
    ll sum = 0;
    for (int i = 1; i <= q; i++) {
        int z = a[i];
        ll val = min(z + s.query(1, z), t.query(z, n+1) - z);
        ll d = abs(z - a[i-1]);
        // since always add whole range, d.
        // we don't need SegLazy, just keep sum
        sum += d;
        z = a[i-1];
        s.better(z, val-z - d); // and here -d, since we don't add it.
        t.better(z, val+z - d);
    }
    ll res = 1e18;
    for (int i = 1; i <= n; i++) {
        ll val = i + s.query_point(i);
        res = min(res, val);
    }
    cout << res + sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
