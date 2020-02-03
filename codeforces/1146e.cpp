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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto& x: a) {
        cin >> x;
    }
    // use gate would be better idea, I{0/1, 0/1} happen to be flip,all0, all1,UN.
    // below single int, space effcient, but easily typo-error
    SegLazy<int,int> s (1<<17, 0b01, 0, -1,
            [](int u, int v){ return 0; }, // no meaning
            [](int& u, int x){
                if (x == 1) {
                    u ^= 3;
                } else if (x != -1) {
                    u = x;
                }
            },
            [](int& x, int y){
                // fuck! silly, NOT 0/1th bit swap, above ^=3, showed flip. why skip x=0,3!!
                //if (y == 3 || y == 0) x = y;
                //else if (y == 1 && (x!=0&&x!=3)) {
                //    x *= -1;
                //}
                if (y == 3 || y == 0) x = y;
                else if (y == 1) {
                    if (x == -1 || x == 1) x *= -1;
                    else x ^= 3;
                }
            }
            );
    while (q--) {
        string t;
        char c; int x;
        cin >> t >> x;
        c = t[0];
        if (c == '<') {
            int y;
            if (x > 0) {
                s.update(0, x, 1);
                y = x;
            } else y = -x + 1;
            s.update(y, 1<<17, 0b00);
        } else {
            assert(c == '>');
            int y;
            if (x < 0) {
                s.update(0, -x, 1);
                y = -x;
            } else y = x + 1;
            //cerr<<x<<' '<< y<<endl;
            s.update(y, 1<<17, 0b11);
        }
    }
    for (int x: a) {
        int d = x>0 ? 1 : 0;
        x = abs(x);
        int z = s.query_point(x);
        int sign = (z>>d&1) ? -1 : 1;
        cout << sign*x << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
