#include <bits/stdc++.h>

using namespace std;

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
    void better(int p, const M& x) {
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

void solve() {
    int n; cin >> n;
    vector<int> b(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int q; cin >> q;
    vector<vector<int>> evs(n+1);
    for (int _ = 0; _ < q; _++) {
        int x,y;
        cin >> x >> y;
        evs[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) {
        sort(evs[i].begin(), evs[i].end());
    }

    SegLazy<int,int> s (n+3, 1e9, 1e9, 0,
            [](int u, int v){ return min(u,v); },
            [](int& u, int x){ u+=x; },
            [](int& x, int y){ x+=y; }
            );
    s.assign(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int r: evs[i]) {
            s.better(r, s.query(0, r));
        }
        if (b[i]) s.update(0, i, 1);
        else s.update(i, n+1, 1);
    }
    cout << s.query(0, n+1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
