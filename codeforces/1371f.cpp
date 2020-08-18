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
        if (d[i]==UN) return; // 2xfaster
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

struct M {
    int l, m, r;
    int ml,mr,n;
    M() {l=m=r=0; ml=mr=n=0;}
    M(int _l, int _m, int _r) : l(_l), m(_m), r(_r) {}
    M(int _l, int _m, int _r, int _ml, int _mr, int _n) : l(_l), m(_m), r(_r),
     ml(_ml), mr(_mr), n(_n){}
    M(bool x) {
        l = x^1; m = 0; r = x;
        ml=mr=n=0;
    }
};
M merge(const M& a, const M& b) {
    //return {a.l, max({a.m, a.r+b.l, b.m}), b.r};
    if (a.r > 0 && b.l > 0) {
        //  > <
        int x = a.r+b.l;
        return {a.l, max({a.m, x, b.m}), b.r, a.n>0?a.ml:x, b.n>0?b.mr:x, a.n + b.n + 1};
    } else if (a.r > 0) {
        if (b.n == 0) {
            // > >>
            return {a.l, a.m, a.r+b.r, a.ml, a.mr, a.n};
        } else {
            // > ><
            int x = a.r+b.ml;
            return {a.l, max({a.m, b.m, x}), b.r, a.n>0?a.ml:x, b.n>1?b.mr:x, a.n+b.n};
        }
    } else if (b.l > 0) {
        if (a.n == 0) {
            // << <
            return {a.l+b.l, b.m, b.r, b.ml, b.mr, b.n};
        } else {
            // >< <
            int x = a.mr+b.l;
            return {a.l, max({a.m, b.m, x}), b.r, a.n>1?a.ml:x, b.n>0?b.mr:x, a.n+b.n};
        }
    } else {
        // <>< ><>
        return {a.l, max(a.m, b.m), b.r, a.n>0?a.ml:b.ml, b.n>0?b.mr:a.mr, a.n+b.n};
    }
}
using B = array<M,2>;

// first note the canonical form is
//   < [><]..[><] >   // note wlog we let > stand for >..>, same <
// since flip range, we maintain by seglazy, a flip flag, and M[2], [0] for now, [1] for if flip.
//
// now let's focus on the moniod M.
//  apparantly we need l = len(<), m = max(len [><]), r = len(>)
// then for merge part we should be careful deal with different case, a.l=?0 b.r?=0, a.m,b.m=?0
//  since these are different merging case
//  thus we need additional info ml/mr:= len of left/right-most [><], and n=#><
void solve() {
    int n,q;
    cin >> n >> q;
    string s; cin >> s;
    vector<B> leaves(n);
    for (int i = 0; i < n; i++) {
        bool x = s[i] == '>';
        leaves[i] = {M(x), M(x^1)};
    }
    SegLazy<B,int> seg(leaves, B{M{}, M{}}, 0,
            [](B u, B v){ return B{merge(u[0],v[0]), merge(u[1],v[1])}; },
            [](B& u, int x){ if(x) swap(u[0],u[1]); },
            [](int& x, int y){ x^=y; }
            );
    while (q--) {
        int l,r;
        cin >> l >> r;
        l--;
        seg.update(l,r,1);
        auto a = seg.query(l,r)[0];
        int res = max({a.l,a.m,a.r});
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
