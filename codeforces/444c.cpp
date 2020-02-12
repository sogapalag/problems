#include <bits/stdc++.h>

using namespace std;
using ll=long long;
struct Node {
    ll sum;
    int sz, col;
    Node() {}
    Node(ll _sum, int _sz, int _col) : sum(_sum), sz(_sz), col(_col) {}
};

template <typename D>
struct SegLazy {
    using M = Node;
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
    SegLazy(const vector<M>& leaves, M _ID, D _UN, Op _op)://, D2M _d2m, D2D _d2d) : 
        ID(_ID), UN(_UN), op(_op)//;, d2m(_d2m), d2d(_d2d)
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
        if (a[i].col != -1) {
            a[i<<1].col = a[i<<1|1].col = a[i].col;
            a[i].col = -1;
        }
        //apply(i<<1, d[i]);
        //apply(i<<1|1, d[i]);
        a[i<<1].sum += a[i<<1].sz * d[i];
        a[i<<1|1].sum += a[i<<1|1].sz * d[i];
        if ((i<<1) < N) d[i<<1] += d[i];
        if ((i<<1|1) < N) d[i<<1|1] += d[i];
        d[i] = UN;
    }
    void update(int l, int r, const D& dval, int i, int sl, int sr) {
        if (r <= sl || sr <= l) return;
        //if (l <= sl && sr <= r) return apply(i, dval);
        if (l <= sl && sr <= r && a[i].col!=-1) {
            a[i].sum += a[i].sz * 1ll * abs(dval - a[i].col);
            if(i<N) d[i] += abs(dval - a[i].col);
            a[i].col = dval;
            return;
        }
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

// awful problem.
void solve() {
    int n,q;
    cin >> n >> q;
    vector<Node> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {0ll, 1, i};
    }

    SegLazy<ll> s (a, {0ll, 0, -1}, 0ll,
            [](Node u, Node v){ return Node{u.sum+v.sum, u.sz+v.sz, u.col==v.col ? u.col : -1}; }
            );
    while (q--) {
        int op,l,r;
        cin >> op >> l >> r;l--;
        if (op == 1) {
            int x; cin >> x; x--;
            s.update(l, r, x);
        } else {
            cout << s.query(l, r).sum << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
