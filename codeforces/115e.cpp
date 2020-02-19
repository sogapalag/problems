#include <bits/stdc++.h>

using namespace std;
using ll=long long;
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
    void update(int p, M val) {
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
template <typename M, typename D>
struct SegLazy {
    using Op = function<M(const M&, const M&)>;
    using D2M = function<void(M&, const D&)>;
    using D2D = function<void(D&, const D&)>;
    
    M ID;
    D UN;
    Op op;
    D2M d2m;
    D2D d2d;

    int N, L;
    vector<M> a; // tree
    vector<D> d; // lazy
    
    SegLazy(int n, M leaf_default, M _ID, D _UN, Op _op, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op), d2m(_d2m), d2d(_d2d)
    {
        init_space(n);
        fill(a.begin() + N, a.begin() + N + n, leaf_default);
        build();
    }
    SegLazy(const vector<M>& leaves, M _ID, D _UN, Op _op, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op), d2m(_d2m), d2d(_d2d)
    {
        int n = leaves.size();
        init_space(n);
        copy(leaves.begin(), leaves.end(), a.begin() + N);
        build();
    }
    void init_space(int n) {
        N = 1; L = 0; while (N < n) N <<= 1, L++;
        a.assign(N<<1, ID);
        d.assign(N, UN);
    }
    inline void pull(int i) { a[i] = op(a[i<<1], a[i<<1|1]); }
    void build() { for (int i = N-1; i >= 1; i--) pull(i); }
    inline int len(int i) {
        return 1 << (L + __builtin_clz(i) - 31);
    }
    inline void apply(int i, const D& dval) {
        d2m(a[i], dval);
        if (i < N) d2d(d[i], dval);
    }
    inline void push(int i) {
        apply(i<<1, d[i]);
        apply(i<<1|1, d[i]);
        d[i] = UN;
    }
    void update(int l, int r, const D& dval, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        if (l <= sl && sr <= r) return apply(i, dval);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        push(i);
        update(l, r, dval, il, sl, sm);
        update(l, r, dval, ir, sm, sr);
        pull(i);
    }
    M query(int l, int r, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return ID;
        if (l <= sl && sr <= r) return a[i];
        push(i);
        int sm = (sl+sr)>>1, il = i<<1, ir = i<<1|1;
        return op(query(l, r, il, sl, sm), query(l, r, ir, sm, sr));
    }

    void update(int l, int r, const D& dval) { 
        assert(0 <= l && r <= N);
        update(l, r, dval, 1, 0, N);
    }
    void assign(int p, const M& x) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        for (a[p] = x; p >>= 1; ) pull(p);

    }
    void update(int p, const M& x) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        for (a[p] = op(a[p], x); p >>= 1; ) pull(p);

    }
    M query(int l, int r) {
        assert(0 <= l && r <= N);
        return query(l, r, 1, 0, N);
    }
    M query_point(int p) {
        assert(0 <= p && p < N);
        p += N;
        for (int k = L; k >= 1; k--) push(p >> k);
        return a[p];
    }
    M query_all() const { return a[1]; }
};

// ugly, dp[r].. used extended to r.  rmx = dp + sum. // one seglazy is enough
void solve() {
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    vector<ll> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + a[i];
    }
    vector<vector<pair<int,int>>> evs(n);
    for (int _ = 0; _ < m; _++) {
        int l,r,x;
        cin >> l >> r >> x;
        l--;
        evs[l].emplace_back(r, x);
    }

    //SegTree<ll> rmx (n + 1, -1e18, -1e18, [](ll u, ll v){ return max(u,v); });
    //SegTree<ll> dp  (n + 1, -1e18, -1e18, [](ll u, ll v){ return max(u,v); });
    SegLazy<ll,ll> rmx (n + 1, -1e18, -1e18, 0,
            [](ll u, ll v){ return max(u,v); },
            [](ll& u, ll x){ u+=x; },
            [](ll& x, ll y){ x+=y; }
            );
    SegLazy<ll,ll> dp (n + 1, -1e18, -1e18, 0,
            [](ll u, ll v){ return max(u,v); },
            [](ll& u, ll x){ u+=x; },
            [](ll& x, ll y){ x+=y; }
            );
    //vector<ll> dp(n + 1, -1e18);
    rmx.assign(0, 0);// dp[0] = 0;
    dp. assign(0, 0);
    for (int l = 0; l < n; l++) {
        sort(evs[l].begin(), evs[l].end());
        for (auto& _: evs[l]) {
            int r, x;
            tie(r, x) = _;
            {// >= r, no cost, so range add +x
                dp.update(r, n+1, x);
                // rmx also
                rmx.update(r, n+1, x);
            }
            // l..r extend to r.  profit - cost
            ll tmp = rmx.query(l, r) - sum[r] + x;
            dp.update(r, tmp);
            rmx.update(r, dp.query_point(r) + sum[r]);
        }
        // prefix, since for l+1, extend to l is like l+1
        dp.update(l+1, dp.query_point(l));
        rmx.update(l+1, dp.query_point(l+1) + sum[l+1]);
    }
    cout << dp.query_point(n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
